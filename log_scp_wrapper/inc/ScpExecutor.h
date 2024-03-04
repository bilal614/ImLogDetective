#pragma once

#include "IScpExecutor.h"
#include <memory>

namespace LogScpWrapper
{

// Uni-directional scp'ing from remote host to local host
class ScpExecutor : public IScpExecutor
{
public:
    ScpExecutor();
    ~ScpExecutor();
    bool setSourceRemoteHostPath(const std::string& remoteHostPath) final;
    RemoteHostPath getSourceRemoteHostPath() final;
    bool setDestinationLocalPath(const std::filesystem::path& localDestinationPath) final;
    std::filesystem::path getDestinationLocalPath() final;
    bool addIdentityFile(const std::filesystem::path& identityFilePath) final;
    std::vector<std::filesystem::path> getIdentityFiles() final;
    bool setJumpHost(const std::string& remoteHostPath) final;
    void copy() final;
    std::string prompt() final;
    void enterPass(const std::string& pass) final;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}