#pragma once

#include <functional>

namespace LogEventHandling
{

template<typename ...A>
class IEvent
{
public:
    virtual ~IEvent() = default;
    virtual void registerDelegate(const std::function<void(A...)>&) = 0;
    virtual void clearDelegates() = 0;
    virtual void operator()(A&&... args) = 0;
};

}