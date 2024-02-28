#pragma once

#include "IScpExecutor.h"

namespace LogScpWrapper
{

// Uni-directional scp'ing from remote host to local host
class ScpExecutor : public IScpExecutor
{
public:
    ScpExecutor();
    ~ScpExecutor() = default;
    bool setSourceRemoteHostPath(const std::string& remoteHostPath) final;
    bool setDestinationLocalPath(const std::filesystem::path& localDestinationPath) final;
    bool setIdentityFile(const std::filesystem::path& identityFilePath) final;
    bool setJumpHost(const std::string& remoteHostPath) final;
    void copy() final;
    std::string prompt() final;
    void enterPass(const std::string& pass) final;
};

}