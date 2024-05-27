#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "ScpWrapper/PtyMaster.h"
#include <fstream>
#include <future>
#include <poll.h>

namespace TestLogScpWrapper
{

using namespace ::testing;

class TestPtyMaster : public ::testing::Test {
protected:
    ::testing::InSequence seq;

    std::string sanitizeNewLineCharacters(const std::string& input);

    TestPtyMaster();
    ~TestPtyMaster() = default;
};

TestPtyMaster::TestPtyMaster()
{
}

std::string TestPtyMaster::sanitizeNewLineCharacters(const std::string& input)
{
    std::string output{input};
    output.erase(std::remove(output.begin(), output.end(), '\r'), output.end());
    output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
    return output;
}

TEST_F(TestPtyMaster, test_PtyMaster_with_tr) {

    std::vector<std::string> testInputs{
        "Hello World!", 
        "Welcome...asdskajshdkjashd",
        "Good Bye!"
    };

    std::vector<std::string> expectedOutput{
        "HELLO WORLD!",
        "WELCOME...ASDSKAJSHDKJASHD",
        "GOOD BYE!"
    };

    ImLogDetective::ProcessStartInfo process_start_info {
        .executable_path{"tr"},
        .arguments{"tr", "a-z", "A-Z"},
    };
    
    std::unique_ptr<ImLogDetective::IPtyMaster> process{std::make_unique<ImLogDetective::PtyMaster>(process_start_info)};

    process->start();

    auto& piped_child = process->getChild();

    process->writeLine(testInputs[0]);

    auto result = process->read(testInputs[0].size() + 2);
    EXPECT_TRUE(result.first);
    EXPECT_EQ(
        result.second,
        sanitizeNewLineCharacters(testInputs[0]));

    result = process->read(expectedOutput[0].size() + 2);
    EXPECT_TRUE(result.first);
    EXPECT_EQ(
        result.second,
        sanitizeNewLineCharacters(expectedOutput[0]));

    process->writeLine(testInputs[1]);

    result = process->read(testInputs[1].size() + 2);
    EXPECT_TRUE(result.first);
    EXPECT_EQ(
        result.second,
        sanitizeNewLineCharacters(testInputs[1]));

    result = process->read(expectedOutput[1].size() + 2);
    EXPECT_TRUE(result.first);
    EXPECT_EQ(
        result.second, 
        sanitizeNewLineCharacters(expectedOutput[1]));

    process->writeLine(testInputs[2]);

    result = process->read(testInputs[2].size() + 2);
    EXPECT_TRUE(result.first);
    EXPECT_EQ(
        result.second, 
        sanitizeNewLineCharacters(testInputs[2]));

    result = process->read(expectedOutput[2].size() + 2);
    EXPECT_TRUE(result.first);
    EXPECT_EQ(
        result.second, 
        sanitizeNewLineCharacters(expectedOutput[2]));

    piped_child.closeMasterChild();

    EXPECT_TRUE(process->kill());
}

TEST_F(TestPtyMaster, test_PtyMaster_with_sh) {

    std::vector<std::string> testInputs{
        "echo Hello World!", 
        "echo Good Bye!"
    };

    std::vector<std::string> expectedOutput{
        "Hello World!",
        "Good Bye!"
    };

    ImLogDetective::ProcessStartInfo process_start_info {
        .executable_path{"sh"},
        .arguments{"sh"},
    };

    std::unique_ptr<ImLogDetective::IPtyMaster> process{std::make_unique<ImLogDetective::PtyMaster>(process_start_info)};

    process->start();

    auto& piped_child = process->getChild();

    process->writeLine(testInputs[0]);

    auto result = process->read(testInputs[0].size() + 2);
    EXPECT_TRUE(result.first);
    EXPECT_EQ(
        result.second,
        sanitizeNewLineCharacters(testInputs[0]));

    result = process->read(expectedOutput[0].size() + 2);
    EXPECT_TRUE(result.first);
    EXPECT_EQ(
        result.second, 
        sanitizeNewLineCharacters(expectedOutput[0]));

    process->writeLine(testInputs[1]);

    result = process->read(testInputs[1].size() + 2);
    EXPECT_TRUE(result.first);
    EXPECT_EQ(
        result.second,
        sanitizeNewLineCharacters(testInputs[1]));

    result = process->read(expectedOutput[1].size() + 2);
    EXPECT_TRUE(result.first);
    EXPECT_EQ(
        result.second, 
        sanitizeNewLineCharacters(expectedOutput[1]));

    piped_child.closeMasterChild();

    EXPECT_TRUE(process->kill());
}

}