#pragma once
#include "IAuthentication.h"

#include <memory>

namespace LogFetchingTool
{

class ISshSession;

class Authentication : public IAuthentication
{
public:
    explicit Authentication(ISshSession& session, const std::string& userName);
    virtual ~Authentication();
    std::vector<AuthenticationMethod> supportedAuthentications() final;
    bool authenticateWithPassword(const std::string& username, const std::string& pass) final;
    bool authenticateWithPublicKey(
        const std::string& username, 
        const std::string& passPhrase,
        const std::filesystem::path& privateKeyFile,
        const std::filesystem::path& publicKeyFile = std::filesystem::path()) final;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}