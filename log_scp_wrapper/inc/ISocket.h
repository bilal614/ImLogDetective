#pragma once
#include <cstddef>

namespace LogScpWrapper
{

typedef int libssh2_socket_t; //Only usable for Linux
using SocketHandle = libssh2_socket_t;

class ISocket
{
public:
    virtual ~ISocket() = default;
    virtual SocketHandle& socketHandle()= 0;
    virtual bool bind() = 0;
    virtual bool listen(unsigned short max_connections) = 0;
    virtual bool accept(SocketHandle& handle) = 0;
    virtual bool connect() = 0;
    virtual size_t send() = 0;
    virtual size_t receive() = 0;
    virtual void setReuseAddress(bool reuse) = 0;
};

}