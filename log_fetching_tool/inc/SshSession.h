#pragma once
#include "ISshSession.h"

#include <memory>

namespace LogFetchingTool
{

class ISocket;

class SshSession : public ISshSession
{
public:
    explicit SshSession(ISocket& socket);
    virtual ~SshSession();
    //bool setOption(ssh_options_e type, const void* value);
    // bool setOption(ssh_options_e type, std::any value) final;
    bool connect() final;
    bool disconnect() final;
    void setBlockingIO(bool blocking) final;
    operator LIBSSH2_SESSION&() final;
    operator LIBSSH2_SESSION*() final;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}