//#include <libssh/libssh.h>
#include <algorithm>
#include <cctype>
#include <libssh2.h>
#include "ForwardChannel.h"
#include "ISshSession.h"
#include <sstream>
#include <unordered_map>
#include <type_traits>
#include <regex>

#include <iostream>


namespace {

int Success = 0;

}

namespace LogFetchingTool
{

struct ForwardChannel::Impl
{
    Impl(ISshSession& session,
        const std::string& host, 
        unsigned int port, 
        const std::string& server_host, 
        unsigned int server_port);
    ~Impl();


    ISshSession& sshSession;
    LIBSSH2_CHANNEL* channel;
    const std::string host;
    unsigned int port;
    const std::string server_host;
    unsigned int server_port;
};

ForwardChannel::Impl::Impl(ISshSession& session, 
    const std::string& host,
    unsigned int port,
    const std::string& server_host, 
    unsigned int server_port) :
    sshSession{session}
{
    channel = libssh2_channel_direct_tcpip_ex(sshSession, 
        host.c_str(),
        port, server_host.c_str(), server_port);
    if(!channel) {
        std::cout << "ForwardChannel:: could not creat channel" << std::endl;
        //Report ERROR
    }
}

ForwardChannel::Impl::~Impl()
{
    if(channel && libssh2_channel_free(channel) != Success)
    {
        std::cout << "Libssh2Channel:: Could not free channel" << std::endl;
    }
}

ForwardChannel::ForwardChannel(ISshSession& session, 
    const std::string& host, 
    unsigned int port,
    const std::string& server_host, 
    unsigned int server_port) :
    p{std::make_unique<Impl>(session, host, port, server_host, server_port)}
{

}

ForwardChannel::~ForwardChannel() = default;

ForwardChannel::operator LIBSSH2_CHANNEL*()
{
    return p->channel;
}

ForwardChannel::operator LIBSSH2_CHANNEL&()
{
    return *p->channel;
}

bool ForwardChannel::read(std::stringstream& data)
{
    char* readData;
    data.get(readData, data.gcount());
    auto len = libssh2_channel_read(p->channel, readData, sizeof(readData));
    return false;
}

bool ForwardChannel::write(const std::string& data)
{
    return false;
}

}