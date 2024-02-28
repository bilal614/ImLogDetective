#pragma once

#include <filesystem>
#include <string>

namespace LogScpWrapper
{

// Uni-directional scp'ing from remote host to local host
class IScpExecutor
{
public:
    virtual ~IScpExecutor() = default;
    virtual bool setSourceRemoteHostPath(const std::string& remoteHostPath) = 0;
    virtual bool setDestinationLocalPath(const std::filesystem::path& localDestinationPath) = 0;
    virtual bool setIdentityFile(const std::filesystem::path& identityFilePath) = 0;
    virtual bool setJumpHost(const std::string& remoteHostPath) = 0;
    virtual void copy() = 0;
    virtual std::string prompt() = 0;
    virtual void enterPass(const std::string& pass) = 0;
};

}