
#include "event_handling/EventLoop.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <chrono>
#include <cstdint>
#include <future>
#include <gmock/gmock-more-actions.h>
#include <gmock/gmock-spec-builders.h>
#include <thread>

namespace TestLogAnalyzerTool
{

using ::testing::StrictMock;

class TestEventLoop : public ::testing::Test {
public:
    ::testing::InSequence seq;

    std::unique_ptr<LogAnalyzerTool::IEventLoop> eventLoop;
    void SetUp() override;
    void TearDown() override;

    TestEventLoop();
    ~TestEventLoop() = default;

};

TestEventLoop::TestEventLoop() :
    eventLoop{std::make_unique<LogAnalyzerTool::EventLoop>()}
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

    auto testThreadId = std::this_thread::get_id();
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
        firstCallback.set_value();
    });

    eventLoop->post([&](){
        testValueBool = expectedTestValueBool;
        ASSERT_NE(testThreadId, std::this_thread::get_id());
        secondCallback.set_value();
    });

    //NOTE: std::function operator() does not use universal references as parameters. Prefer to pass ref parameters if 
    // you expect to use them as inout arguments
    eventLoop->post<LogAnalyzerTool::EventLoop, void, const int&, const float&, float&>({[&](const int& a, const float& b, float& c){
        c = a*b;
        ASSERT_NE(testThreadId, std::this_thread::get_id());
        thirdCallback.set_value();
    }}, 5, 7.0f, testValueFloat);

    firstCallbackFuture.get();
    EXPECT_EQ(testValueInt, expectedTestValueInt);

    secondCallbackFuture.get();
    EXPECT_EQ(testValueBool, expectedTestValueBool);

    thirdCallbackFuture.get();
    EXPECT_FLOAT_EQ(testValueFloat, expectedValueFloat);
}

}