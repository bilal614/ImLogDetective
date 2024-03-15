
#include "log_scp_wrapper/AuthenticationWorkFlow.h"
#include "log_scp_wrapper/RemoteHost.h"
#include <iostream>
#include <regex>
#include <utility>
#include <vector>

namespace {
    std::regex hostAuthenticityPrompt{"The authenticity of host.*yes/no.*\?"};
}

namespace LogScpWrapper
{

struct AuthenticationWorkFlow::Impl {
    Impl();
    ~Impl() = default;

    RemoteHost checkHostAuthenticationFrom(const std::string& prompt);
    std::filesystem::path checkKeyAuthenticationFrom(const std::string& prompt);

    std::vector<RemoteHost> remoteHosts;
    std::vector<std::filesystem::path> keyFiles;
};

AuthenticationWorkFlow::Impl::Impl() : 
    remoteHosts{},
    keyFiles{}
{
}

RemoteHost AuthenticationWorkFlow::Impl::checkHostAuthenticationFrom(const std::string& prompt)
{
    for(const auto& host : remoteHosts)
    {
        if(prompt.find(host.toString()) != std::string::npos)
        {
            return host;
        }
    }
    return RemoteHost{};
}

std::filesystem::path AuthenticationWorkFlow::Impl::checkKeyAuthenticationFrom(const std::string& prompt)
{
    if(!keyFiles.empty())
    {
        for(const auto& keyFile : keyFiles)
        {
            if(prompt.find(keyFile.string()) != std::string::npos)
            {
                return keyFile;
            }
        }
    }
    return std::filesystem::path{};
}

AuthenticationWorkFlow::AuthenticationWorkFlow() :
    p{std::make_unique<Impl>()}
{
}

AuthenticationWorkFlow::~AuthenticationWorkFlow() = default;


void AuthenticationWorkFlow::addRemoteHost(const RemoteHost& host)
{
    if(!host.empty())
    {
        p->remoteHosts.push_back(host);
    }

}

void AuthenticationWorkFlow::addKeyFile(const std::filesystem::path& filePath)
{
    p->keyFiles.push_back(filePath);
}

AuthenticationRequest AuthenticationWorkFlow::validatePrompt(const std::string& prompt)
{
    AuthenticationRequest request{PromptType::None, std::string{}};

    auto host = p->checkHostAuthenticationFrom(prompt);
    if(!host.empty())
    {
        std::cout << "UserAuthentication" << std::endl;
        request.prompt = PromptType::UserAuthentication;
        request.data = host.toString();
    }
    auto keyFile = p->checkKeyAuthenticationFrom(prompt);
    if(!keyFile.empty())
    {
        std::cout << "KeyFileAuthentication" << std::endl;
        request.prompt = PromptType::KeyFileAuthentication;
        request.data = keyFile.string();
    }

    std::smatch found_matches;
    if (std::regex_match(prompt, found_matches, hostAuthenticityPrompt) && !found_matches.empty())
    {
        std::cout << "HostAuthenticity" << std::endl;
        request.prompt = PromptType::HostAuthenticity;
        request.data = prompt;
    }

    return request;
}

}