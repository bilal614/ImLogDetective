#pragma once
#include <chrono>
#include <functional>

namespace LogFetchingTool
{

using FileDescriptor = int;

class IIOMultiPlexor
{
public:
    virtual ~IIOMultiPlexor() = default;
    virtual void setFileDescriptor(const FileDescriptor& fd) = 0;
    virtual void waitOnReady(const std::chrono::seconds& timeout) = 0;
    virtual void setOnIoReadyCallback(const std::function<void()>& callback) = 0;
};

}