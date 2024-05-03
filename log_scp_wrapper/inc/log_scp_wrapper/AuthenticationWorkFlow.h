#pragma once

#include "IAuthenticationWorkFlow.h"
#include <memory>

namespace LogScpWrapper
{

class AuthenticationWorkFlow : public IAuthenticationWorkFlow
{
public:
    AuthenticationWorkFlow();
    ~AuthenticationWorkFlow();
    void addRemoteHost(const RemoteHost& host) final;
    void addKeyFile(const std::filesystem::path& filePath) final;
    AuthenticationRequest validatePrompt(std::string prompt) final;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}