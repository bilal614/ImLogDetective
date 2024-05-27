#include "ScpWrapper/ScpExecutor.h"
#include "EventHandling/IEventLoop.h"
#include "ScpWrapper/IAuthenticationWorkFlow.h"
#include "ScpWrapper/RemoteHost.h"
#include "ScpWrapper/PtyMaster.h"

#include <condition_variable>
#include <coroutine>
#include <fstream>
#include <future>
#include <mutex>
#include <iostream>
#include <regex>
#include <unordered_set>

namespace {
    const std::regex KeyEncapsulationBoundaryHeaderBegin{"-----BEGIN.*-----"};
    const std::regex KeyEncapsulationBoundaryHeaderEnd{"-----END.*-----"};
    const std::regex DownloadStarted{"\\S*\\s*.*[0-9]{1,3}%.*/s.*:.*"};
    const std::string AddHostResponseYes{"yes"};
    const std::string AddHostResponseNo{"no"};
    const std::string ScpTool{"scp"};
}

namespace ImLogDetective
{

struct ScpExecutor::Impl
{
    Impl(LogEventHandling::IEventLoop& eventLoop, 
        IAuthenticationWorkFlow& authenticationWorkFlow);
    ~Impl() = default;

    bool extractRemoteHostFrom(const std::string& remoteHost, RemoteHost& host);
    bool checkKeyEncapsulationBoundaryFormat(
        const std::filesystem::path& identityFilePath
    );
    ProcessStartInfo prepareProcessStartInfo();
    bool hasDownloadStarted();

    void setPrompt(const std::string& input);
    std::string getPrompt();
    void setAuthenticationRequest(const AuthenticationRequest& req);
    AuthenticationRequest getAuthenticationRequest();

    std::mutex mtx, mtx_prompt, mtx_request;
    RemoteHostPath remoteHostPath;
    std::filesystem::path destinationLocalPath;
    std::unordered_set<std::filesystem::path> identityFilePaths;
    std::unordered_set<RemoteHost, RemoteHostHash> jumpHosts;
    LogEventHandling::IEventLoop& eventLoop;
    IAuthenticationWorkFlow& authenticationWorkFlow;
    std::unique_ptr<std::promise<bool>> copyWillBeFinished;
    std::future<bool> copyHasFinished;
    bool downloadHasFinished;
    std::condition_variable userInput;
    bool userInputRequired;
    std::unique_ptr<IPtyMaster> process;
    AuthenticationRequest request;
    std::string prompt;
};

ScpExecutor::Impl::Impl(LogEventHandling::IEventLoop& eventLoop, 
    IAuthenticationWorkFlow& authenticationWorkFlow) :
        remoteHostPath{},
        destinationLocalPath{},
        identityFilePaths{},
        jumpHosts{},
        eventLoop{eventLoop},
        authenticationWorkFlow{authenticationWorkFlow},
        process{nullptr},
        userInputRequired{true},
        request{},
        copyWillBeFinished{nullptr},
        downloadHasFinished{false}
{
}

bool ScpExecutor::Impl::extractRemoteHostFrom(const std::string& remoteHost, RemoteHost& host)
{
    bool result = false;
    try
    {
        if(remoteHost.find(AT_SYMBOL) != std::string::npos)
        {
            host.user = remoteHost.substr(0, remoteHost.find(AT_SYMBOL));
            host.ip = remoteHost.substr(
                remoteHost.find(AT_SYMBOL) + 1, 
                remoteHost.find(COLON_SYMBOL) - remoteHost.find(AT_SYMBOL) - 1);
            result = true;
            authenticationWorkFlow.addRemoteHost(host);
        }
    }
    catch (const std::out_of_range& ex)
    {
        std::cerr << ex.what()  << std::endl;
        result = false;
    }
    return result;
}

bool ScpExecutor::Impl::checkKeyEncapsulationBoundaryFormat(
    const std::filesystem::path& identityFilePath)
{
    bool result = false;
    std::ifstream idFile(identityFilePath);
    std::string firstLine, lastLine;
    if (idFile.good())
    {
        std::getline(idFile, firstLine);
        while (idFile >> std::ws && std::getline(idFile, lastLine));
    }
    std::smatch found_matches;
    if ((std::regex_match(firstLine, found_matches, KeyEncapsulationBoundaryHeaderBegin) && !found_matches.empty()) &&
        (std::regex_match(lastLine, found_matches, KeyEncapsulationBoundaryHeaderEnd) && !found_matches.empty()))
    {
        result = true;
    }
    return result;
}

ProcessStartInfo ScpExecutor::Impl::prepareProcessStartInfo()
{
    ProcessStartInfo process_start_info {
            .executable_path{ScpTool},
    };
    process_start_info.arguments.emplace_back("-r");
    if(!identityFilePaths.empty())
    {
        process_start_info.arguments.emplace_back("-i");
        std::vector<std::string> identityFiles;
        std::transform(identityFilePaths.cbegin(), identityFilePaths.cend(), std::back_inserter(identityFiles),
                [](const std::filesystem::path& path) { return path.string(); });
        process_start_info.arguments.insert(process_start_info.arguments.end(), 
            identityFiles.begin(), identityFiles.end());
    }
    if(!jumpHosts.empty())
    {
        process_start_info.arguments.emplace_back("-J");
        std::vector<std::string> jumpHostsArgs;
        std::transform(jumpHosts.cbegin(), jumpHosts.cend(), std::back_inserter(jumpHostsArgs),
                [](const RemoteHost& host) { return host.toString(); });
        process_start_info.arguments.insert(process_start_info.arguments.end(), 
            jumpHostsArgs.begin(), jumpHostsArgs.end());
    }

    process_start_info.arguments.push_back(remoteHostPath.toString());
    process_start_info.arguments.push_back(destinationLocalPath.string());
    return process_start_info;
}

void ScpExecutor::Impl::setPrompt(const std::string& input)
{
    std::lock_guard<std::mutex> lk(mtx_prompt);
    prompt = input;
}

std::string ScpExecutor::Impl::getPrompt()
{
    std::lock_guard<std::mutex> lk(mtx_prompt);
    return prompt;
}

void ScpExecutor::Impl::setAuthenticationRequest(const AuthenticationRequest& req)
{
    //std::lock_guard<std::mutex> lk(mtx_request);
    request = req;
}

AuthenticationRequest ScpExecutor::Impl::getAuthenticationRequest()
{
    //std::lock_guard<std::mutex> lk(mtx_request);
    return request;
}

bool ScpExecutor::Impl::hasDownloadStarted()
{
    auto prompt = getPrompt();
    std::smatch found_matches;
    if (std::regex_match(prompt, found_matches, DownloadStarted))
    {
        return true;
    }
    return false;
}

ScpExecutor::ScpExecutor(LogEventHandling::IEventLoop& eventLoop, 
    IAuthenticationWorkFlow& authenticationWorkFlow) :
        p{std::make_unique<Impl>(eventLoop, authenticationWorkFlow)}
{
}

ScpExecutor::~ScpExecutor() = default;

bool ScpExecutor::setSourceRemoteHostPath(const std::string& remoteHostPath)
{
    bool result = false;
    try
    {
        result = p->extractRemoteHostFrom(remoteHostPath, p->remoteHostPath.host)
            && remoteHostPath.find(COLON_SYMBOL) != std::string::npos;
        if(result)
        {
            p->remoteHostPath.sourcePath = remoteHostPath.substr(
                remoteHostPath.find(COLON_SYMBOL) + 1, 
                remoteHostPath.size() - remoteHostPath.find(COLON_SYMBOL) - 1);
        }
    }
    catch (const std::out_of_range& ex)
    {
        std::cerr << ex.what()  << std::endl;
        result = false;
    }
    return result;
}

RemoteHostPath ScpExecutor::getSourceRemoteHostPath()
{
    return p->remoteHostPath;
}

bool ScpExecutor::setDestinationLocalPath(const std::filesystem::path& localDestinationPath)
{
    bool result = false;

    if(!std::filesystem::exists(localDestinationPath))
    {
        result = std::filesystem::create_directories(localDestinationPath);
        if(std::filesystem::is_directory(localDestinationPath) && std::filesystem::exists(localDestinationPath))
        {
            p->destinationLocalPath = localDestinationPath;
        }
    }
    else
    {
        p->destinationLocalPath = localDestinationPath;
        result = true;
    }
    return result;
}

std::filesystem::path ScpExecutor::getDestinationLocalPath()
{
    return p->destinationLocalPath;
}

bool ScpExecutor::addIdentityFile(const std::filesystem::path& identityFilePath)
{
    bool result = false;

    if(std::filesystem::exists(identityFilePath) && std::filesystem::is_regular_file(identityFilePath))
    {
        if(p->checkKeyEncapsulationBoundaryFormat(identityFilePath))
        {
            p->identityFilePaths.emplace(identityFilePath);
            p->authenticationWorkFlow.addKeyFile(identityFilePath);
            result = true;
        }
    }
    return result;
}

std::unordered_set<std::filesystem::path> ScpExecutor::getIdentityFiles()
{
    return p->identityFilePaths;
}

bool ScpExecutor::addJumpHost(const std::string& remoteHost)
{
    RemoteHost host;
    if(p->extractRemoteHostFrom(remoteHost, host))
    {
        p->jumpHosts.emplace(host);
        return true;
    }
    return false;
}

std::unordered_set<RemoteHost, RemoteHostHash> ScpExecutor::getJumpHosts()
{
    return p->jumpHosts;
}

void ScpExecutor::download()
{
    p->eventLoop.post([this](){
        ProcessStartInfo process_start_info = p->prepareProcessStartInfo();

        p->process = std::make_unique<ImLogDetective::PtyMaster>(process_start_info);
        p->process->start();
        auto& piped_child = p->process->getChild();

        {
            std::lock_guard<std::mutex> lk(p->mtx);
            p->copyWillBeFinished.reset();
            p->copyWillBeFinished = std::make_unique<std::promise<bool>>();
            p->downloadHasFinished = false;
        }
        auto hasInput = true;
        do
        {
            auto result = p->process->read();
            hasInput = result.first;
            p->setPrompt(result.second);

            if(!p->hasDownloadStarted())
            {
                p->setAuthenticationRequest(p->authenticationWorkFlow.validatePrompt(p->getPrompt()));
                if(p->getAuthenticationRequest().prompt != PromptType::None)
                {
                    std::unique_lock lk(p->mtx);
                    p->userInputRequired = true;
                    p->userInput.wait(lk);
                }
            } else {
                std::cout << p->getPrompt() << std::endl;
            }
        } while(hasInput);

        piped_child.closeMasterChild();
        {
            std::lock_guard<std::mutex> lk(p->mtx);
            p->copyWillBeFinished->set_value(true);
        }
        p->process.reset();
    });
}

bool ScpExecutor::downloadStarted()
{
    return p->hasDownloadStarted();
}

bool ScpExecutor::downloadFinished()
{
    std::lock_guard<std::mutex> lk(p->mtx);
    if(p->copyWillBeFinished)
    {
        if(!p->copyHasFinished.valid() && !p->downloadHasFinished)
        {
            p->copyHasFinished = p->copyWillBeFinished->get_future();
        }
        auto status = p->copyHasFinished.wait_for(std::chrono::milliseconds(0));
        if(p->copyHasFinished.valid() && status == std::future_status::ready)
        {
            p->downloadHasFinished = p->copyHasFinished.get();
            p->copyWillBeFinished.reset();
        }
    }
    return p->downloadHasFinished;
}

AuthenticationRequest ScpExecutor::getAuthenticationRequest()
{
    return p->getAuthenticationRequest();
}

std::string ScpExecutor::prompt()
{
    return p->prompt;
}

bool ScpExecutor::passRequired()
{
    std::lock_guard<std::mutex> lk(p->mtx);
    return p->userInputRequired;
}

void ScpExecutor::enterPass(const std::string& pass)
{
    //std::lock_guard<std::mutex> lk(p->mtx);
    p->process->writeLine(pass);
    p->process->read();
    {
        std::lock_guard<std::mutex> lk(p->mtx);
        p->userInputRequired = false;
    }
    p->setAuthenticationRequest(AuthenticationRequest{PromptType::None, std::string{}});
    p->userInput.notify_one();
}

}
