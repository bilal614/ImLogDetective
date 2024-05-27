
#include "EventHandling/EventLoop.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <chrono>
#include <future>
#include <thread>

namespace TestLogEventHandling
{

using namespace std::chrono_literals;

class TestEventLoop : public ::testing::Test {
public:
    ::testing::InSequence seq;

    std::unique_ptr<LogEventHandling::IEventLoop> eventLoop;
    void SetUp() override;
    void TearDown() override;

    TestEventLoop();
    ~TestEventLoop() = default;

};

TestEventLoop::TestEventLoop() :
    eventLoop{std::make_unique<LogEventHandling::EventLoop>()}
{
}

void TestEventLoop::SetUp()
{
    eventLoop->start();
}

void TestEventLoop::TearDown()
{
    eventLoop->stop();
}

TEST_F(TestEventLoop, test_posting_on_fifo_eventloop) {

    const auto testThreadId = std::this_thread::get_id();
    uint32_t testValueInt = 7;
    bool testValueBool = false;
    float testValueFloat = 0.0f;
    auto addressOfTestValueFloat = &testValueFloat;

    const uint32_t expectedTestValueInt = 10;
    const bool expectedTestValueBool = true;
    const float expectedValueFloat = 5*7.0f;

    std::promise<void> firstCallback;
    std::promise<void> secondCallback;
    std::promise<void> thirdCallback;

    std::future<void> firstCallbackFuture = firstCallback.get_future();
    std::future<void> secondCallbackFuture = secondCallback.get_future();
    std::future<void> thirdCallbackFuture = thirdCallback.get_future();

    ASSERT_NE(testValueInt, expectedTestValueInt);
    ASSERT_NE(testValueBool, expectedTestValueBool);

    eventLoop->post([&](){
        testValueInt = expectedTestValueInt;
        ASSERT_NE(testThreadId, std::this_thread::get_id());
        ASSERT_EQ(eventLoop->size(), 0);
        firstCallback.set_value();
    });

    firstCallbackFuture.get();
    EXPECT_EQ(testValueInt, expectedTestValueInt);

    eventLoop->post([&](){
        testValueBool = expectedTestValueBool;
        ASSERT_NE(testThreadId, std::this_thread::get_id());
        //Long lasting task execution should still allow new callbacks to be post'ed on FIFO queue
        std::this_thread::sleep_for(1000ms);
        ASSERT_EQ(eventLoop->size(), 1);
        secondCallback.set_value();
    });

    eventLoop->post<LogEventHandling::EventLoop, void, const int&, const float&, float&>({[&](const int& a, const float& b, float& c){
        c = a*b;
        ASSERT_NE(testThreadId, std::this_thread::get_id());
        thirdCallback.set_value();
    }}, 5, 7.0f, testValueFloat);

    secondCallbackFuture.get();
    EXPECT_EQ(testValueBool, expectedTestValueBool);

    thirdCallbackFuture.get();
    EXPECT_FLOAT_EQ(testValueFloat, expectedValueFloat);

}

}