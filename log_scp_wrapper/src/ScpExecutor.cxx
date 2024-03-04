#include "ScpExecutor.h"
#include <fstream>
#include <iostream>
#include <regex>

namespace {
    constexpr char AT_SYMBOL{'@'};
    constexpr char COLON_SYMBOL{':'};
    const std::regex KeyEncapsulationBoundaryHeaderBegin{"-----BEGIN.*-----"};
    const std::regex KeyEncapsulationBoundaryHeaderEnd{"-----END.*-----"};
}

namespace LogScpWrapper
{

struct ScpExecutor::Impl
{

    Impl();
    ~Impl() = default;

    bool checkKeyEncapsulationBoundaryFormat(
        const std::filesystem::path& identityFilePath
    );

    RemoteHostPath remoteHostPath;
    std::filesystem::path destinationLocalPath;
    std::vector<std::filesystem::path> identityFilePaths;
};

ScpExecutor::Impl::Impl() :
    remoteHostPath{},
    destinationLocalPath{},
    identityFilePaths{}
{
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

ScpExecutor::ScpExecutor() :
    p{std::make_unique<Impl>()}
{

}

ScpExecutor::~ScpExecutor() = default;

bool ScpExecutor::setSourceRemoteHostPath(const std::string& remoteHostPath)
{
    if(remoteHostPath.find(AT_SYMBOL) == std::string::npos || remoteHostPath.find(COLON_SYMBOL) == std::string::npos)
    {
        return false;
    }
    try
    {
        p->remoteHostPath.user = remoteHostPath.substr(0, remoteHostPath.find(AT_SYMBOL));
        p->remoteHostPath.host = remoteHostPath.substr(
            remoteHostPath.find(AT_SYMBOL) + 1, 
            remoteHostPath.find(COLON_SYMBOL) - remoteHostPath.find(AT_SYMBOL) - 1);
        p->remoteHostPath.sourcePath = remoteHostPath.substr(
            remoteHostPath.find(COLON_SYMBOL) + 1, 
            remoteHostPath.size() - remoteHostPath.find(COLON_SYMBOL) - 1);
    }
    catch (const std::out_of_range& ex)
    {
        std::cerr << ex.what()  << std::endl;
        return false;
    }

    return true;
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
            p->identityFilePaths.emplace_back(identityFilePath);
            result = true;
        }
    }
    return result;
}

std::vector<std::filesystem::path> ScpExecutor::getIdentityFiles()
{
    return p->identityFilePaths;
}

bool ScpExecutor::setJumpHost(const std::string& remoteHostPath)
{
    return false;
}

void ScpExecutor::copy()
{
}

std::string ScpExecutor::prompt()
{
    return std::string();
}

void ScpExecutor::enterPass(const std::string& pass)
{

}

}
