#pragma once

#include <functional>

namespace LogAnalyzerTool
{

class IEvent
{
public:
    virtual ~IEvent() = default;
    
    virtual void registerDelegate(const std::function<void()>&) = 0;

    virtual void clearDelegates() = 0;

    virtual void operator()() = 0;
};

}