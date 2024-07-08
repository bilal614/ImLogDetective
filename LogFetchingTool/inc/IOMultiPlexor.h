#pragma once
#include "IIOMultiPlexor.h"
#include <functional>
#include <memory>

namespace LogFetchingTool
{

class IOMultiPlexor : public IIOMultiPlexor
{
public:
    IOMultiPlexor();
    ~IOMultiPlexor();
    void setFileDescriptor(const FileDescriptor& fd) final;
    void waitOnReady(const std::chrono::seconds& timeout) final;
    void setOnIoReadyCallback(const std::function<void()>& callback) final;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}