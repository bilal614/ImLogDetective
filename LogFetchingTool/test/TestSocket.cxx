#include "Socket.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <future>
#include <thread>

namespace TestLogFetchingTool
{

using namespace ::testing;
using ::testing::StrictMock;
using namespace LogFetchingTool;

class TestSocket : public ::testing::Test {
protected:
    ::testing::InSequence seq;

    std::string ipAddress;
    unsigned int portNr;
    Socket server;

    TestSocket();
    ~TestSocket() = default;
};

TestSocket::TestSocket() :
    ipAddress{"127.0.0.1"},
    portNr{49255},
    server{ipAddress, portNr}
{

}


TEST_F(TestSocket, test_trivial_socket_can_connect)
{
    ASSERT_TRUE(server.bind());
    ASSERT_TRUE(server.listen(1));

    auto task = std::async(std::launch::async, [&]()
    {
        SocketHandle acceptedHandle;
        return server.accept(acceptedHandle);
    });

    Socket clientSocket{ipAddress, portNr};
    ASSERT_TRUE(clientSocket.connect());

    ASSERT_TRUE(task.get());

}

}