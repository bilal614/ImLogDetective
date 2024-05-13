#pragma once

#include <filesystem>
#include <string>
#include <vector>
#include <unordered_set>

namespace ImLogDetective
{

struct AuthenticationRequest;
struct RemoteHost;
struct RemoteHostPath;
struct RemoteHostHash;

// Uni-directional scp'ing from remote host to local host
class IScpExecutor
{
public:
    virtual ~IScpExecutor() = default;
    virtual bool setSourceRemoteHostPath(const std::string& remoteHostPath) = 0;
    virtual RemoteHostPath getSourceRemoteHostPath() = 0;
    virtual bool setDestinationLocalPath(const std::filesystem::path& localDestinationPath) = 0;
    virtual std::filesystem::path getDestinationLocalPath() = 0;
    virtual bool addIdentityFile(const std::filesystem::path& identityFilePath) = 0;
    virtual std::unordered_set<std::filesystem::path> getIdentityFiles() = 0;
    virtual bool addJumpHost(const std::string& remoteHost) = 0;
    virtual std::unordered_set<RemoteHost, RemoteHostHash> getJumpHosts() = 0;
    virtual void download() = 0;
    virtual bool downloadStarted() = 0;
    virtual bool downloadFinished() = 0;
    virtual std::string prompt() = 0;
    virtual AuthenticationRequest getAuthenticationRequest() = 0;
    virtual bool passRequired() = 0;
    virtual void enterPass(const std::string& pass) = 0;
};

}