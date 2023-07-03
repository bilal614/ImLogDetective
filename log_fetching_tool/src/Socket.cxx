#include "Socket.h"
#include <cstddef>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cerrno>
#include <sys/time.h>
#include <unistd.h>
#include <libssh2.h>

#include <iostream>

namespace{

const int Unsuccesful = -1;

}

namespace LogFetchingTool
{

using SocketAddress = struct sockaddr_in;
constexpr socklen_t sinlen(SocketAddress){ 
    return sizeof(SocketAddress);
}

struct Socket::Impl
{
    Impl(const std::string& server_ip, unsigned int port_number);
    ~Impl();
    void setSocketOption(int option_name, int option_value);
    bool connect();
    bool initSocketAddress(const std::string& server_ip,  unsigned int port_number);

    SocketAddress socket_address;
    socklen_t sin_length;
    int sock;
    int sockopt;
};    

Socket::Impl::Impl(const std::string& server_ip, unsigned int port_number) :
    sock{socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)}
{
    if(sock == Unsuccesful)
    {
        std::cout << "Socket:: Could not create socket" << strerror(errno) << std::endl;
        //ERROR: Report error
    } else {
        std::cout << "Socket:: sock=" << sock << std::endl;
    }

    initSocketAddress(server_ip, port_number);
}

bool Socket::Impl::initSocketAddress(const std::string& server_ip,  unsigned int port_number)
{
    memset(&socket_address, 0, sizeof(socket_address));
    socket_address.sin_family = AF_INET;
    inet_pton(AF_INET, server_ip.c_str(), &socket_address.sin_addr);
    //socket_address.sin_addr.s_addr = inet_addr(server_ip.c_str());
    if(INADDR_NONE == socket_address.sin_addr.s_addr) 
    {
        std::cout << "Socket:: Could not translate ip address" << strerror(errno) << std::endl;
        //ERROR Report error
        return false;
    }
    socket_address.sin_port = htons(port_number);
    sin_length = sinlen(socket_address);
    return true;
}

Socket::Impl::~Impl()
{
    if(::close(sock) != 0)
    {
        std::cout << "Socket:: ERROR could not correctly close socket, error=" 
            << strerror(errno) << std::endl;
    } else {
        std::cout << "Socket:: socket closed" << std::endl;
    }
}

void Socket::Impl::setSocketOption(int option_name, int option_value)
{
    sockopt = option_value;
    setsockopt(sock, SOL_SOCKET, option_name, &sockopt,
               sizeof(sockopt));
}

bool Socket::Impl::connect()
{
    if(::connect(sock, (struct sockaddr*)(&socket_address),
                sinlen(socket_address)) != 0) 
    {
        std::cout << "Socket:: Failed to connect, error" << strerror(errno)
            << ", ip=" << inet_ntoa(socket_address.sin_addr) << std::endl;
        return false;
    }
    return true;
}

Socket::Socket(const std::string& server_ip, unsigned int port_number) :
    p{std::make_unique<Impl>(server_ip, port_number)}
{
}

Socket::~Socket() = default;

SocketHandle& Socket::socketHandle()
{
    return p->sock;
}

bool Socket::bind()
{
    if(::bind(p->sock, (struct sockaddr *)&(p->socket_address), sinlen(p->socket_address)) == Unsuccesful) 
    {
        //Report ERROR
        std::cout << "ERROR Socket::bind" << std::endl;
        return false;
    }
    return true;
}

bool Socket::listen(unsigned short max_connections)
{
    if(::listen(p->sock, max_connections) == Unsuccesful) 
    {
        // Report ERROR
        return false;
    }
    return true;
}

bool Socket::accept(SocketHandle& handle)
{
    handle = ::accept(p->sock, (struct sockaddr *)&(p->socket_address), &(p->sin_length));
    if(handle == LIBSSH2_INVALID_SOCKET) 
    {
        std::cout << "ERROR Socket::accept" << std::endl;
        return false;
    }
    return true;
}

bool Socket::connect()
{
    return p->connect();
}

size_t Socket::send()
{
    return 0;
}

size_t Socket::receive()
{
    return 0;
}

void Socket::setReuseAddress(bool reuse)
{
    p->setSocketOption(SO_REUSEADDR, reuse ? 1 : 0);
}

void Socket::getSocketInfo()
{
    struct sockaddr_in sin;
    socklen_t sinlen = sizeof(sin);
    ::getsockname(p->sock, (struct sockaddr *)&sin, &(sinlen));

    //std::cout << "sock: " << 
}

};