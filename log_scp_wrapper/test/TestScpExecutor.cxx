#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "ScpExecutor.h"
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

    LogScpWrapper::ScpExecutor scpExecutor;
    const std::filesystem::path testDirPath;
    const std::filesystem::path testRelativePath;
    const std::filesystem::path testKeyFile1, testKeyFile2, testKeyFile3;
};

TestScpExecutor::TestScpExecutor() :
    scpExecutor{},
    testDirPath{"./tst"},
    testRelativePath{"./tst/dir/path"},
    testKeyFile1{testDirPath/"keyFile1"},
    testKeyFile2{testDirPath/"keyFile2"},
    testKeyFile3{testDirPath/"keyFile3"}
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
        std::ofstream strm{testKeyFile3};
        strm << "----begin asjkdlasjd----" << std::endl;
        strm << "non-compliant_key_headers" << std::endl;
        strm << "-----foo end-----" << std::endl;
        EXPECT_TRUE(std::filesystem::exists(testKeyFile3));
    }
}

void TestScpExecutor::TearDown() 
{
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
    const std::string expectedHost{"127.0.1"};
    const std::filesystem::path expectedRemotePath{"/fake/remote/path"};

    EXPECT_TRUE(scpExecutor.setSourceRemoteHostPath(remoteHostPath));

    auto sourceRemoteHostPath = scpExecutor.getSourceRemoteHostPath();

    EXPECT_EQ(sourceRemoteHostPath.user, expectedUser);
    EXPECT_EQ(sourceRemoteHostPath.host, expectedHost);
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
    EXPECT_FALSE(scpExecutor.addIdentityFile(testKeyFile3));

    auto identityFiles = scpExecutor.getIdentityFiles();

    EXPECT_EQ(identityFiles.size(), expectedNumberOfValidKeysAdded);
    EXPECT_EQ(identityFiles[0], testKeyFile1);
    EXPECT_EQ(identityFiles[1], testKeyFile2);
}

}