#pragma once

#include "ISocket.h"
#include <memory>
#include <string>

namespace LogScpWrapper
{

class Socket : public ISocket
{
public:
    Socket(const std::string& server_ip, unsigned int port_number);
    ~Socket();
    SocketHandle& socketHandle() final;
    bool bind() final;
    bool listen(unsigned short max_connections) final;
    bool accept(SocketHandle& handle) final;
    bool connect() final;
    size_t send() final;
    size_t receive() final;
    void setReuseAddress(bool reuse) final;
    void getSocketInfo();
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}