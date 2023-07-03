#pragma once
#include "IChannel.h"
#include <memory>
#include <string>

namespace LogFetchingTool
{

class ISshSession;

class ForwardChannel : public IChannel
{
public:
    ForwardChannel(ISshSession& session, 
        const std::string& host, 
        unsigned int port,
        const std::string& server_host, 
        unsigned int server_port);
    ~ForwardChannel();
    bool read(std::stringstream& data) final;
    bool write(const std::string& data) final;
    operator LIBSSH2_CHANNEL*();
    operator LIBSSH2_CHANNEL&();
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}