#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace {
    constexpr char AT_SYMBOL{'@'};
    constexpr char COLON_SYMBOL{':'};
}

namespace LogScpWrapper
{

struct RemoteHost
{
    std::string user;
    std::string ip;
    std::string toString() const
    {
         return user + AT_SYMBOL + ip;
    }
    bool operator==(const RemoteHost& host) const
    {
        return ip == host.ip && user == host.user;
    }
    bool operator!=(const RemoteHost& host) const
    {
        return !(*this == host);
    }
    bool empty() const
    {
        return user.empty() && ip.empty();
    }
};

struct RemoteHostPath
{
    RemoteHost host;
    std::filesystem::path sourcePath;
    std::string toString() const
    {
        return host.toString() + COLON_SYMBOL + sourcePath.string();
    }
};

}