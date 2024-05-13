#pragma once

#include "event_handling/IEvent.h"
#include "gmock/gmock.h"

namespace TestImLogDetective {

template<typename ...A>
class EventMock : public LogEventHandling::IEvent<A...>
{
public:
    MOCK_METHOD(void, registerDelegate, (const std::function<void(A...)>&));
    MOCK_METHOD(void, clearDelegates, ());
    MOCK_METHOD(void, functionCallOperator, (A&&... args));
    virtual void operator()(A&&... args) override
    {
        return functionCallOperator(std::forward<A>(args)...);
    }
};

}