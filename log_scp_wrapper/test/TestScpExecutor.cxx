#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "log_scp_wrapper/AuthenticationWorkFlow.h"
#include "log_scp_wrapper/RemoteHost.h"
#include "log_scp_wrapper/ScpExecutor.h"
#include "event_handling/EventLoop.h"
#include <fstream>
#include <future>
#include <poll.h>

namespace TestLogScpWrapper
{

using namespace ::testing;

class TestScpExecutor : public ::testing::Test {
protected:
    ::testing::InSequence seq;

    TestScpExecutor();
    ~TestScpExecutor() = default;

    void SetUp() final;
    void TearDown() final;

    LogEventHandling::EventLoop eventLoop;
    ImLogDetective::AuthenticationWorkFlow authenticationWorkFlow;
    ImLogDetective::ScpExecutor scpExecutor;
    const std::filesystem::path testDirPath;
    const std::filesystem::path testRelativePath;
    const std::filesystem::path testKeyFile1, testKeyFile2, invalidKeyFile;
    const std::string remoteHost1, remoteHost2, invalidRemoteHost;
};

TestScpExecutor::TestScpExecutor() :
    eventLoop{},
    authenticationWorkFlow{},
    scpExecutor{eventLoop, authenticationWorkFlow},
    testDirPath{"./tst"},
    testRelativePath{"./tst/dir/path"},
    testKeyFile1{testDirPath/"keyFile1"},
    testKeyFile2{testDirPath/"keyFile2"},
    invalidKeyFile{testDirPath/"invalidKeyFile"},
    remoteHost1{"foo@192.168.1.1"},
    remoteHost2{"bar@192.168.1.2"},
    invalidRemoteHost{"bla-192.168.1.3"}
{
}

void TestScpExecutor::SetUp()
{
    std::filesystem::remove_all(testDirPath);
    EXPECT_TRUE(std::filesystem::create_directories(testDirPath));
    {
        std::ofstream strm{testKeyFile1};
        strm << "-----BEGIN OPENSSH PRIVATE KEY-----" << std::endl;
        strm << "key1=fooBar-Barfoo" << std::endl;
        strm << "Barfoo_fooBar=" << std::endl;
        strm << "-----END OPENSSH PRIVATE KEY-----" << std::endl;
        EXPECT_TRUE(std::filesystem::exists(testKeyFile1));
    }
    {
        std::ofstream strm{testKeyFile2};
        strm << "-----BEGIN OPENSSH PRIVATE KEY-----" << std::endl;
        strm << "key2=fooBar-Barfoo" << std::endl;
        strm << "Barfoo_fooBar=" << std::endl;
        strm << "-----END OPENSSH PRIVATE KEY-----" << std::endl;
        EXPECT_TRUE(std::filesystem::exists(testKeyFile2));
    }
    {
        std::ofstream strm{invalidKeyFile};
        strm << "----begin asjkdlasjd----" << std::endl;
        strm << "non-compliant_key_headers" << std::endl;
        strm << "-----foo end-----" << std::endl;
        EXPECT_TRUE(std::filesystem::exists(invalidKeyFile));
    }
    eventLoop.start();
}

void TestScpExecutor::TearDown() 
{
    eventLoop.stop();
    std::filesystem::remove_all(testDirPath);
}

TEST_F(TestScpExecutor, test_ScpExecutor_setSourceRemoteHostPath_with_incorrect_input_missing_symbols) {

    const std::string remoteHostPathWithoutAtSymbol {"my_user127.0.1:/fake/remote/path"};
    const std::string remoteHostPathWithoutColonSymbol {"my_user@127.0.1/fake/remote/path"};
    const std::string remoteHostPathWithoutDelimitationSymbols {"my_user127.0.1/fake/remote/path"};

    EXPECT_FALSE(scpExecutor.setSourceRemoteHostPath(remoteHostPathWithoutAtSymbol));
    EXPECT_FALSE(scpExecutor.setSourceRemoteHostPath(remoteHostPathWithoutColonSymbol));
    EXPECT_FALSE(scpExecutor.setSourceRemoteHostPath(remoteHostPathWithoutDelimitationSymbols));
}

TEST_F(TestScpExecutor, test_ScpExecutor_setSourceRemoteHostPath_with_valid_input) {

    const std::string remoteHostPath {"my_user@127.0.1:/fake/remote/path"};
    const std::string expectedUser{"my_user"};
    const std::string expectedIp{"127.0.1"};
    const std::filesystem::path expectedRemotePath{"/fake/remote/path"};

    EXPECT_TRUE(scpExecutor.setSourceRemoteHostPath(remoteHostPath));

    auto sourceRemoteHostPath = scpExecutor.getSourceRemoteHostPath();

    EXPECT_EQ(sourceRemoteHostPath.host.user, expectedUser);
    EXPECT_EQ(sourceRemoteHostPath.host.ip, expectedIp);
    EXPECT_EQ(sourceRemoteHostPath.sourcePath, expectedRemotePath);
}

TEST_F(TestScpExecutor, test_ScpExecutor_setDestinationLocalPath_creates_recursively_destination_folder) {
    EXPECT_TRUE(scpExecutor.setDestinationLocalPath(testRelativePath));
    EXPECT_EQ(scpExecutor.getDestinationLocalPath(), testRelativePath);
}

TEST_F(TestScpExecutor, test_ScpExecutor_setDestinationLocalPath_assigns_existing_destination_folder) {
    EXPECT_TRUE(scpExecutor.setDestinationLocalPath(testDirPath));
    EXPECT_EQ(scpExecutor.getDestinationLocalPath(), testDirPath);
}

TEST_F(TestScpExecutor, test_ScpExecutor_addIdentityFile_add_nonexistent_identity_file) {
    EXPECT_FALSE(scpExecutor.addIdentityFile(testDirPath/"non_existent_key_file"));
}

TEST_F(TestScpExecutor, test_ScpExecutor_addIdentityFile_add_existing_identity_file_with_valid_headers) {

    const size_t expectedNumberOfValidKeysAdded = 2;
    
    EXPECT_TRUE(scpExecutor.addIdentityFile(testKeyFile1));
    EXPECT_TRUE(scpExecutor.addIdentityFile(testKeyFile2));
    EXPECT_FALSE(scpExecutor.addIdentityFile(invalidKeyFile));

    auto identityFiles = scpExecutor.getIdentityFiles();

    EXPECT_EQ(identityFiles.size(), expectedNumberOfValidKeysAdded);
    EXPECT_TRUE(identityFiles.find(testKeyFile1) != identityFiles.end());
    EXPECT_TRUE(identityFiles.find(testKeyFile2) != identityFiles.end());
    EXPECT_EQ(*identityFiles.find(testKeyFile1), testKeyFile1);
    EXPECT_EQ(*identityFiles.find(testKeyFile2), testKeyFile2);
}

TEST_F(TestScpExecutor, test_ScpExecutor_addJumpHost_only_valid_jump_hosts_will_be_added) {

    const size_t expectedNumberOfValidKeysAdded = 2;
    const std::string user1{"foo"}, user2{"bar"};
    const std::string ip1{"192.168.1.1"}, ip2{"192.168.1.2"};
    ImLogDetective::RemoteHost expectedHost1{user1, ip1}, expectedHost2{user2, ip2};

    EXPECT_TRUE(scpExecutor.addJumpHost(remoteHost1));
    EXPECT_TRUE(scpExecutor.addJumpHost(remoteHost2));
    EXPECT_FALSE(scpExecutor.addJumpHost(invalidRemoteHost));

    auto jumpHosts = scpExecutor.getJumpHosts();

    EXPECT_EQ(jumpHosts.size(), expectedNumberOfValidKeysAdded);
    EXPECT_TRUE(jumpHosts.find(expectedHost1) != jumpHosts.end());
    EXPECT_TRUE(jumpHosts.find(expectedHost2) != jumpHosts.end());
    EXPECT_EQ(jumpHosts.find(expectedHost1)->ip, ip1);
    EXPECT_EQ(jumpHosts.find(expectedHost1)->user, user1);
    EXPECT_EQ(jumpHosts.find(expectedHost2)->ip, ip2);
    EXPECT_EQ(jumpHosts.find(expectedHost2)->user, user2);
}

}