#include <libssh2.h>
#include "SshSession.h"
#include "LibSsh2Init.h"
#include "ISocket.h"

#include <memory>
#include <type_traits>

#include <iostream>

namespace LogFetchingTool
{
struct SshSession::Impl
{
    Impl(ISocket& socket);
    ~Impl() = default;

    struct Libssh2Session{
        Libssh2Session()
        {
            _session = libssh2_session_init();
            if(_session != nullptr)
            {
                std::cout << "Libssh2Session:: session initialized" << std::endl;
            } else {
                std::cout << "Libssh2Session:: ERROR session not initialized" << std::endl;
            }

        }
        ~Libssh2Session()
        {
            if(_session && libssh2_session_free(_session) != 0)
            {
                std::cout << "Libssh2Session:: Could not free ssh session" << std::endl;
            }
        }
        operator LIBSSH2_SESSION*()
        {
            return _session;
        }
        operator LIBSSH2_SESSION&()
        {
            return *_session;
        }
        private:
            LIBSSH2_SESSION* _session;
    };

    bool verifyConnectedHost();

    std::unique_ptr<Libssh2Session> session;
    bool connectedSession;
    ISocket& socket;
};

SshSession::Impl::Impl(ISocket& socket) :
    session{nullptr},
    socket{socket},
    connectedSession{false}
{
    LibSsh2Init::getInstance();

    session = std::make_unique<Libssh2Session>();

    if(!socket.connect())
    {
        //Report ERROR
        std::cout << "SshSession:: unable to connect socket" << std::endl;
    } else {
        connectedSession = true;
    }
}

SshSession::SshSession(ISocket& socket) : 
    p{std::make_unique<Impl>(socket)}
{

}

SshSession::~SshSession() = default;

bool SshSession::connect()
{
    //NOTE later handle each error code separately
    if(libssh2_session_handshake(*p->session, p->socket.socketHandle()) != 0)
    {
        std::cout << "SshSession:: Error when starting up SSH session" << std::endl;
        // Report ERROR
    } else {
        p->connectedSession = true;
    }
    return p->connectedSession;
}

bool SshSession::disconnect()
{
    //NOTE later handle each error code separately
    if(libssh2_session_disconnect(*p->session, "shutdown") != 0)
    {
        //Report ERROR
        std::cout << "SshSession:: Unable to disconnect" << std::endl;
    } else {
        p->connectedSession = false;
    }
    return !p->connectedSession;
}

void SshSession::setBlockingIO(bool blocking)
{
    libssh2_session_set_blocking(*p->session, blocking ? 1 : 0);
}

SshSession::operator LIBSSH2_SESSION&() 
{
    return *p->session;
}

SshSession::operator LIBSSH2_SESSION*()
{
    return *p->session;
}

}