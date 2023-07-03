#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Authentication.h"
#include "SshSession.h"
#include "Socket.h"

namespace TestLogFetchingTool
{

TEST(TestSocket, TestSocket) {

    const auto server_ip = "127.0.0.1";
    LogFetchingTool::Socket socket{server_ip, 8080}; //On my machine I have Jenkins running on that port
    ASSERT_TRUE(socket.connect());
}

}