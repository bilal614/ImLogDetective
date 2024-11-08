#include "models/LogDataModelImpl.h"
#include "models/LogLine.h"
#include "TestUtility.h"
#include "gtest/gtest.h"
#include <filesystem>

namespace TestImLogDetective
{

using namespace ImLogDetective;
using namespace ::testing;

TEST(TestLogDataModelImpl, test_LogDataModelImpl_added_log_lines_must_have_correct_log_level_assigned) 
{
    const std::string debugLogPrefix = "DEBUG";
    const std::string infoogPrefix = "INFO";
    const std::string warningLogPrefix = "WARNING";
    const std::string errorLogPrefix = "ERROR";
    const std::string datatSource = "TestData";
    std::vector<std::string> logLines{
        "hello world 1", 
        debugLogPrefix + " hello world 2", 
        infoogPrefix + " hello world 3", 
        warningLogPrefix + " foo bar", 
        errorLogPrefix + " bar foo", 
        "bla bla bla"
    };

    ImLogDetective::LogDataModelImpl logDataModelImpl{datatSource};

    EXPECT_FALSE(logDataModelImpl.getCompleted());

    std::for_each(logLines.begin(), logLines.end(), [&](const std::string& line){
        logDataModelImpl.addLogData(line);
    });

    auto logData = logDataModelImpl.getLogData();
    EXPECT_EQ(logData.size(), logLines.size());

    std::for_each(logData.begin(), logData.end(), [&](const LogLine& logLine)
    {
        EXPECT_THAT(logLines, Contains(logLine.logLine));
    });

    EXPECT_EQ(logData[0].level, LogLevel::Unknown);
    EXPECT_EQ(logData[1].level, LogLevel::Debug);
    EXPECT_EQ(logData[2].level, LogLevel::Info);
    EXPECT_EQ(logData[3].level, LogLevel::Warning);
    EXPECT_EQ(logData[4].level, LogLevel::Error);
    EXPECT_EQ(logData[5].level, LogLevel::Unknown);

    logDataModelImpl.setCompleted(true);
    EXPECT_TRUE(logDataModelImpl.getCompleted());

}

}