#include "IOMultiPlexor.h"
#include <bits/types/struct_timeval.h>
#include <sys/select.h>
#include <sys/time.h>

namespace{

constexpr int SelectTimeoutResult = 0;
constexpr int SelectError = -1;
constexpr bool selectSucceeded(const int& selectResult){ return selectResult > SelectTimeoutResult;};

}

namespace LogFetchingTool
{

struct IOMultiPlexor::Impl
{
    Impl();
    ~Impl() = default;

    FileDescriptor fileDescriptorHandle;
    std::function<void()> callback;
    fd_set file_descriptor_set;

    void setFileDescriptor(const FileDescriptor& fd);
};

IOMultiPlexor::Impl::Impl()
{
    FD_ZERO(&file_descriptor_set);
}

void IOMultiPlexor::Impl::setFileDescriptor(const FileDescriptor& fd)
{
    FD_SET(fd, &file_descriptor_set);
}

IOMultiPlexor::IOMultiPlexor() :
    p{std::make_unique<Impl>()}
{

}

IOMultiPlexor::~IOMultiPlexor() = default;

void IOMultiPlexor::setFileDescriptor(const FileDescriptor& fd)
{
    p->setFileDescriptor(fd);
}

void IOMultiPlexor::waitOnReady(const std::chrono::seconds& timeout)
{
    struct timeval tv;
    tv.tv_sec = timeout.count();
    auto result = select((int)(p->fileDescriptorHandle + 1), &(p->file_descriptor_set), nullptr, nullptr, &tv);
    if(result == SelectTimeoutResult)
    {
        //report Timeout
    }

    if(result == SelectError)
    {
        // Report ERROR
    }

    if(selectSucceeded(result) && FD_ISSET(p->fileDescriptorHandle, &p->file_descriptor_set))
    {
        p->callback();
    }
}

void IOMultiPlexor::setOnIoReadyCallback(const std::function<void()>& callback)
{
    p->callback = callback;
}

}