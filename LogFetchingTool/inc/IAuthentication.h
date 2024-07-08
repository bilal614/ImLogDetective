#pragma once

#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>

namespace LogFetchingTool
{

enum class AuthenticationMethod {
    HostBased,
    Interactive,
    Password,
    PublicKey,
};

class IAuthentication
{
public:
    virtual ~IAuthentication() = default;
    virtual std::vector<AuthenticationMethod> supportedAuthentications() = 0;
    virtual bool authenticateWithPassword(const std::string& username, const std::string& pass) = 0;
    virtual bool authenticateWithPublicKey(
        const std::string& username, 
        const std::string& passPhrase,
        const std::filesystem::path& privateKeyFile,
        const std::filesystem::path& publicKeyFile = std::filesystem::path()) = 0;
};

}