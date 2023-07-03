#pragma once

typedef struct _LIBSSH2_SESSION LIBSSH2_SESSION;

namespace LogFetchingTool
{

class ISshSession
{
public:
    virtual ~ISshSession() = default;
    virtual bool connect() = 0;
    virtual bool disconnect() = 0;
    virtual void setBlockingIO(bool blocking) = 0;
    virtual operator LIBSSH2_SESSION&() = 0;
    virtual operator LIBSSH2_SESSION*() = 0;
};

}