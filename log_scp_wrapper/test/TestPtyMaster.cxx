#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "PtyMaster.h"
#include <fstream>
#include <future>
#include <poll.h>

namespace TestLogFetchingTool
{

using namespace ::testing;

class TestPtyMaster : public ::testing::Test {
protected:
    ::testing::InSequence seq;

    void addFdToFdSet(int fileDescriptor);
    bool awaitDataOn(int fileDescriptor);

    void writeTo(int fileDescriptor, const std::string& input);
    std::string readFrom(int fileDescriptor, size_t bytesToRead);

    std::string sanitizeNeLineCharacters(const std::string& input);

    TestPtyMaster();
    ~TestPtyMaster() = default;

    fd_set rfds;
    struct timeval tv;

    char rd_buf[1024];
    char wr_buf[1024];
    ssize_t bytes_read;
};

TestPtyMaster::TestPtyMaster() :
   tv{.tv_sec=5, .tv_usec=0},
   rd_buf{0},
   wr_buf{0},
   bytes_read{0}
{
    FD_ZERO(&rfds);
}

void TestPtyMaster::addFdToFdSet(int fileDescriptor)
{
    FD_SET(fileDescriptor, &rfds);
}

bool TestPtyMaster::awaitDataOn(int fileDescriptor)
{
    int retval = select(fileDescriptor+1, &rfds, NULL, NULL, &tv);
    if (retval >= 1)
    {
        return true;
    }
    return false;
}

void TestPtyMaster::writeTo(int fileDescriptor, const std::string& input)
{
    memset(wr_buf, 0, 1024);
    strcpy(wr_buf, input.c_str());
    write(fileDescriptor, wr_buf, strlen(wr_buf));
}

std::string TestPtyMaster::readFrom(int fileDescriptor, size_t bytesToRead)
{
    if (awaitDataOn(fileDescriptor))
    {
        memset(rd_buf, 0, 1024);
        bytes_read = read(fileDescriptor, rd_buf, bytesToRead);
        return rd_buf;
    }
    return std::string{};
}

std::string TestPtyMaster::sanitizeNeLineCharacters(const std::string& input)
{
    std::string output{input};
    output.erase(std::remove(output.begin(), output.end(), '\r'), output.end());
    output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
    return output;
}

TEST_F(TestPtyMaster, test_PtyMaster_with_tr) {

    std::vector<std::string> testInputs{
        "Hello World!\n", 
        "Welcome...asdskajshdkjashd\n",
        "Good Bye!\n"
    };

    std::vector<std::string> expectedOutput{
        "HELLO WORLD!",
        "WELCOME...ASDSKAJSHDKJASHD",
        "GOOD BYE!"
    };

    LogScpWrapper::ProcessStartInfo process_start_info {
        .executable_path{"tr"},
        .arguments{"tr", "a-z", "A-Z"},
    };
    
    std::unique_ptr<LogScpWrapper::IPtyMaster> process{std::make_unique<LogScpWrapper::PtyMaster>(process_start_info)};

    process->start();

    auto& piped_child = process->getChild();

    addFdToFdSet(piped_child.master_fd);

    writeTo(piped_child.master_fd, testInputs[0]);

    EXPECT_EQ(
        sanitizeNeLineCharacters(readFrom(piped_child.master_fd, testInputs[0].size() + 1)), 
        sanitizeNeLineCharacters(testInputs[0]));

    EXPECT_EQ(
        sanitizeNeLineCharacters(readFrom(piped_child.master_fd, expectedOutput[0].size() + 2)), 
        sanitizeNeLineCharacters(expectedOutput[0]));

    writeTo(piped_child.master_fd, testInputs[1]);

    EXPECT_EQ(
        sanitizeNeLineCharacters(readFrom(piped_child.master_fd, testInputs[1].size() + 1)), 
        sanitizeNeLineCharacters(testInputs[1]));

    EXPECT_EQ(
        sanitizeNeLineCharacters(readFrom(piped_child.master_fd, expectedOutput[1].size() + 2)), 
        sanitizeNeLineCharacters(expectedOutput[1]));


    writeTo(piped_child.master_fd, testInputs[2]);

    EXPECT_EQ(
        sanitizeNeLineCharacters(readFrom(piped_child.master_fd, testInputs[2].size() + 1)), 
        sanitizeNeLineCharacters(testInputs[2]));

    EXPECT_EQ(
        sanitizeNeLineCharacters(readFrom(piped_child.master_fd, expectedOutput[2].size() + 2)), 
        sanitizeNeLineCharacters(expectedOutput[2]));

    piped_child.closeMasterChild();

}


TEST_F(TestPtyMaster, test_PtyMaster_with_sh) {

    std::vector<std::string> testInputs{
        "echo Hello World!\n", 
        "echo Good Bye!\n"
    };

    std::vector<std::string> expectedOutput{
        "Hello World!",
        "Good Bye!"
    };

    LogScpWrapper::ProcessStartInfo process_start_info {
        .executable_path{"sh"},
        .arguments{"sh"},
    };

    std::unique_ptr<LogScpWrapper::IPtyMaster> process{std::make_unique<LogScpWrapper::PtyMaster>(process_start_info)};

    process->start();

    auto& piped_child = process->getChild();

    addFdToFdSet(piped_child.master_fd);

    writeTo(piped_child.master_fd, testInputs[0]);

    EXPECT_EQ(
        sanitizeNeLineCharacters(readFrom(piped_child.master_fd, testInputs[0].size() + 1)), 
        sanitizeNeLineCharacters(testInputs[0]));

    EXPECT_EQ(
        sanitizeNeLineCharacters(readFrom(piped_child.master_fd, expectedOutput[0].size() + 2)), 
        sanitizeNeLineCharacters(expectedOutput[0]));

    writeTo(piped_child.master_fd, testInputs[1]);

    EXPECT_EQ(
        sanitizeNeLineCharacters(readFrom(piped_child.master_fd, testInputs[1].size() + 1)), 
        sanitizeNeLineCharacters(testInputs[1]));

    EXPECT_EQ(
        sanitizeNeLineCharacters(readFrom(piped_child.master_fd, expectedOutput[1].size() + 2)), 
        sanitizeNeLineCharacters(expectedOutput[1]));

    piped_child.closeMasterChild();
}

}