
#include "EventHandling/Event.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

namespace TestLogEventHandling
{

using namespace std::chrono_literals;

class TestEvent : public ::testing::Test {
public:
    using DelegateFunction = std::function<void(int, float, std::string)>;
    using DelegateFuncSingleArg = std::function<void(int)>;
};

TEST_F(TestEvent, test_callbacks_are_executed_when_event_occurs) {

    LogEventHandling::Event<int, float, std::string> event;

    size_t registeredDelegateCount = 0;

    const int expectedInt = 7;
    const float expectedFloat = 3.14159;
    const std::string expectedStr = "foo bar";

    DelegateFunction testFuncDelegate = [&] (int a, float b, std::string c) -> void {
        registeredDelegateCount++;
        ASSERT_EQ(expectedInt, a);
        ASSERT_FLOAT_EQ(expectedFloat, b);
        ASSERT_EQ(expectedStr, c);
    };

    event.registerDelegate(testFuncDelegate);
    event.registerDelegate(testFuncDelegate);
    event.registerDelegate(testFuncDelegate);

    event(7, 3.14159, "foo bar");

    ASSERT_EQ(registeredDelegateCount, 3);
    event.clearDelegates();
    event(7, 3.14159, "foo bar");
    ASSERT_EQ(registeredDelegateCount, 3);
}

TEST_F(TestEvent, test_callbacks_are_executed_and_finally_completion_handler_is_invoked_when_event_occurs) {

    bool completionHandlerInvoked = false;
    LogEventHandling::Event<int> event{[&](){
        completionHandlerInvoked = true;
    }};

    const int expectedInt = 7;
    DelegateFuncSingleArg testFuncDelegate = [&] (int a) -> void {
        ASSERT_EQ(expectedInt, a);
    };

    ASSERT_FALSE(completionHandlerInvoked);
    event(7);
    ASSERT_TRUE(completionHandlerInvoked);
}

}