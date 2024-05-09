#pragma once

#include <cstdint>
#include <filesystem>
#include <istream>
#include <ostream>
#include <string>
#include <vector>


#include <unistd.h>

namespace LogScpWrapper
{

struct pty_child {
    pid_t pid;
    int master_fd;
    bool master_fd_closed;

    pty_child() :
        pid{-1},
        master_fd{-1},
        master_fd_closed{false}
    {
    }

    ~pty_child()
    {
    }

    void closeMasterChild()
    {
        close(master_fd);
        master_fd_closed = true;
    }
};

struct ProcessStartInfo{
    std::filesystem::path executable_path;
    std::vector<std::string> arguments;
};

class IPtyMaster
{
public:
    virtual ~IPtyMaster() = default;
    virtual void start() = 0;
    virtual void waitForExit() = 0;
    virtual bool kill() = 0;
    virtual std::filesystem::path getCurrentWorkingDirectory() = 0;
    virtual uint32_t getPid() = 0;
    virtual std::string getUser() = 0;
    virtual pty_child& getChild() = 0;
    //Pty IO
    virtual void writeLine(const std::string& input) = 0;
    virtual std::pair<bool, std::string> read(size_t bytesToRead) = 0;
    virtual std::pair<bool, std::string> read() = 0;
};

}