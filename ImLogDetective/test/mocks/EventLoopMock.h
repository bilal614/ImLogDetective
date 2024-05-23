#pragma once

#include "event_handling/IEventLoop.h"
#include "gmock/gmock.h"

namespace TestImLogDetective {

class EventLoopMock : public LogEventHandling::IEventLoop 
{
public:
    MOCK_METHOD(size_t, size,());
    MOCK_METHOD(void, post, (const std::function<void()>&));
    MOCK_METHOD(void, post,(void (*)()));
    MOCK_METHOD(void, start, ());
    MOCK_METHOD(void, stop, ());
};

}