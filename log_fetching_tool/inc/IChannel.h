#pragma once
#include <string>

namespace LogFetchingTool
{

typedef struct _LIBSSH2_CHANNEL LIBSSH2_CHANNEL;
typedef struct _LIBSSH2_LISTENER LIBSSH2_LISTENER;

class IChannel
{
public:
    virtual ~IChannel() = default;
    virtual bool read(std::stringstream& data) = 0;
    virtual bool write(const std::string& data) = 0;
};

}