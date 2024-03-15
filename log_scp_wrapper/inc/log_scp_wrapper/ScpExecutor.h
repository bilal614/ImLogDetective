#pragma once

#include "IScpExecutor.h"
#include <memory>

namespace LogEventHandling {
    class IEventLoop;
}

namespace LogScpWrapper
{

struct AuthenticationRequest;
class IAuthenticationWorkFlow;
// Uni-directional scp'ing from remote host to local host
class ScpExecutor : public IScpExecutor
{
public:
    ScpExecutor(LogEventHandling::IEventLoop& eventLoop, IAuthenticationWorkFlow& authenticationWorkFlow);
    ~ScpExecutor();
    bool setSourceRemoteHostPath(const std::string& remoteHostPath) final;
    RemoteHostPath getSourceRemoteHostPath() final;
    bool setDestinationLocalPath(const std::filesystem::path& localDestinationPath) final;
    std::filesystem::path getDestinationLocalPath() final;
    bool addIdentityFile(const std::filesystem::path& identityFilePath) final;
    std::vector<std::filesystem::path> getIdentityFiles() final;
    bool addJumpHost(const std::string& remoteHost) final;
    std::vector<RemoteHost> getJumpHosts() final;
    void download() final;
    bool downloadStarted() final;
    bool downloadFinished() final;
    std::string prompt() final;
    AuthenticationRequest getAuthenticationRequest() final;
    bool passRequired() final;
    void enterPass(const std::string& pass) final;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}