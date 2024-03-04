#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace LogScpWrapper
{

struct RemoteHostPath
{
    std::string user;
    std::string host;
    std::filesystem::path sourcePath;
};

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
    virtual std::vector<std::filesystem::path> getIdentityFiles() = 0;
    virtual bool setJumpHost(const std::string& remoteHostPath) = 0;
    virtual void copy() = 0;
    virtual std::string prompt() = 0;
    virtual void enterPass(const std::string& pass) = 0;
};

}