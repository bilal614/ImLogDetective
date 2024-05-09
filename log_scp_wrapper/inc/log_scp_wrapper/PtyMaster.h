#pragma once
#include "IPtyMaster.h"
#include <string>
#include <memory>

namespace LogScpWrapper
{

class PtyMaster : public IPtyMaster
{
public:
    PtyMaster(const ProcessStartInfo& processStartInfo);
    ~PtyMaster();
    void start() final;
    void waitForExit() final;
    bool kill() final;
    std::filesystem::path getCurrentWorkingDirectory() final;
    uint32_t getPid() final;
    std::string getUser() final;
    pty_child& getChild() final;
    void writeLine(const std::string& input) final;
    std::pair<bool, std::string> read(size_t bytesToRead) final;
    std::pair<bool, std::string> read() final;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}