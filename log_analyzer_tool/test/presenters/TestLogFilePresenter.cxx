#include "LogAnalyzerToolDefs.h"
#include "presenters/LogFilePresenter.h"
#include "mocks/LogDataModelMock.h"
#include "mocks/LogFileParserMock.h"
#include "mocks/LogFilterViewMock.h"
#include "mocks/LogViewMock.h"
#include "mocks/ScopedImGuiWindowMock.h"
#include "mocks/WindowFactoryMock.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <filesystem>
#include <memory>
#include <unordered_map>

namespace TestLogAnalyzerTool
{

using ::testing::StrictMock;

class TestLogFilePresenter : public ::testing::Test {
protected:
    ::testing::InSequence seq;

    LogDataModelMock logDataModelMock;
    LogFileParserMock logFileParserMock;
    LogFilterViewMock logFilterViewMock;
    LogViewMock logViewMock;
    ScopedImGuiWindowMock scopedImGuiWindowMock;
    WindowFactoryMock windowFactoryMock;

    std::filesystem::path filePath;
    std::unordered_map<LogAnalyzerTool::LogLevel, std::string> dummyLogLines;
    const std::vector<LogAnalyzerTool::LogData> dummyLogData;

    void SetUp() override;

    LogAnalyzerTool::LogFilePresenter logFilePresenter;

    TestLogFilePresenter();
    ~TestLogFilePresenter() = default;
};

TestLogFilePresenter::TestLogFilePresenter() :
    logFilePresenter{windowFactoryMock,
        logFilterViewMock,
        logViewMock,
        logFileParserMock, 
        logDataModelMock},
    filePath{"/fake/path"},
    dummyLogLines{{LogAnalyzerTool::LogLevel::Debug, "11:51:45,518 - DEBUG - Foo.Bar - foo bar"},
        {LogAnalyzerTool::LogLevel::Info, "11:51:45,527 - INFO - Lorem.Ipsum - lorem ipsum"},
        {LogAnalyzerTool::LogLevel::Warning, "11:51:45,718 - WARNING - Excepteur.Sint - Excepteur sint"},
        {LogAnalyzerTool::LogLevel::Error, "11:51:46,318 - ERROR - Nemo.Enim - Nemo enim"}
        },
    dummyLogData {
        LogAnalyzerTool::LogData{dummyLogLines[LogAnalyzerTool::LogLevel::Debug], LogAnalyzerTool::LogLevel::Debug},
        LogAnalyzerTool::LogData{dummyLogLines[LogAnalyzerTool::LogLevel::Info], LogAnalyzerTool::LogLevel::Info},
        LogAnalyzerTool::LogData{dummyLogLines[LogAnalyzerTool::LogLevel::Warning], LogAnalyzerTool::LogLevel::Warning},
        LogAnalyzerTool::LogData{dummyLogLines[LogAnalyzerTool::LogLevel::Error], LogAnalyzerTool::LogLevel::Error}
    }
{

}

void TestLogFilePresenter::SetUp()
{
    ::testing::InSequence seq;

}

TEST_F(TestLogFilePresenter, test_logFilePresenter_update_debug_info_warning_error_checked) {

    EXPECT_CALL(windowFactoryMock, createChildWindow(LogAnalyzerTool::LogFilterChildWindow)).Times(1);
    EXPECT_CALL(logFilterViewMock, drawFilterCheckBoxes()).Times(1);
    EXPECT_CALL(windowFactoryMock, createChildWindow(LogAnalyzerTool::LogFileContentChildWindow)).Times(1);
    EXPECT_CALL(logFileParserMock, readLogFileData(::testing::_, ::testing::_)).Times(1);

    EXPECT_CALL(logDataModelMock, getLogData()).WillOnce(testing::ReturnRef(dummyLogData));

    EXPECT_CALL(logFilterViewMock, getDebugChecked()).WillOnce(::testing::Return(true));
    EXPECT_CALL(logViewMock, drawLogLineText(::testing::Eq(std::string_view(dummyLogLines[LogAnalyzerTool::LogLevel::Debug])), 
        LogAnalyzerTool::TextColor::White));
    
    EXPECT_CALL(logFilterViewMock, getInfoChecked()).WillOnce(::testing::Return(true));
    EXPECT_CALL(logViewMock, drawLogLineText(::testing::Eq(std::string_view(dummyLogLines[LogAnalyzerTool::LogLevel::Info])), 
        LogAnalyzerTool::TextColor::White));

    EXPECT_CALL(logFilterViewMock, getWarningChecked()).WillOnce(::testing::Return(true));
    EXPECT_CALL(logViewMock, drawLogLineText(::testing::Eq(std::string_view(dummyLogLines[LogAnalyzerTool::LogLevel::Warning])), 
        LogAnalyzerTool::TextColor::Orange));

    EXPECT_CALL(logFilterViewMock, getErrorChecked()).WillOnce(::testing::Return(true));
    EXPECT_CALL(logViewMock, drawLogLineText(::testing::Eq(std::string_view(dummyLogLines[LogAnalyzerTool::LogLevel::Error])), 
        LogAnalyzerTool::TextColor::Red));

    logFilePresenter.update(filePath);
}

TEST_F(TestLogFilePresenter, test_logFilePresenter_update_info_warning_error_checked) {

    EXPECT_CALL(windowFactoryMock, createChildWindow(LogAnalyzerTool::LogFilterChildWindow)).Times(1);
    EXPECT_CALL(logFilterViewMock, drawFilterCheckBoxes()).Times(1);
    EXPECT_CALL(windowFactoryMock, createChildWindow(LogAnalyzerTool::LogFileContentChildWindow)).Times(1);
    EXPECT_CALL(logFileParserMock, readLogFileData(::testing::_, ::testing::_)).Times(1);


    EXPECT_CALL(logDataModelMock, getLogData()).WillOnce(testing::ReturnRef(dummyLogData));

    EXPECT_CALL(logFilterViewMock, getDebugChecked()).WillOnce(::testing::Return(false));

    EXPECT_CALL(logFilterViewMock, getInfoChecked()).WillOnce(::testing::Return(true));
    EXPECT_CALL(logViewMock, drawLogLineText(::testing::Eq(std::string_view(dummyLogLines[LogAnalyzerTool::LogLevel::Info])), 
        LogAnalyzerTool::TextColor::White));

    EXPECT_CALL(logFilterViewMock, getWarningChecked()).WillOnce(::testing::Return(true));
    EXPECT_CALL(logViewMock, drawLogLineText(::testing::Eq(std::string_view(dummyLogLines[LogAnalyzerTool::LogLevel::Warning])), 
        LogAnalyzerTool::TextColor::Orange));

    EXPECT_CALL(logFilterViewMock, getErrorChecked()).WillOnce(::testing::Return(true));
    EXPECT_CALL(logViewMock, drawLogLineText(::testing::Eq(std::string_view(dummyLogLines[LogAnalyzerTool::LogLevel::Error])), 
        LogAnalyzerTool::TextColor::Red));

    logFilePresenter.update(filePath);
}

TEST_F(TestLogFilePresenter, test_logFilePresenter_update_warning_error_checked) {

    EXPECT_CALL(windowFactoryMock, createChildWindow(LogAnalyzerTool::LogFilterChildWindow)).Times(1);
    EXPECT_CALL(logFilterViewMock, drawFilterCheckBoxes()).Times(1);
    EXPECT_CALL(windowFactoryMock, createChildWindow(LogAnalyzerTool::LogFileContentChildWindow)).Times(1);
    EXPECT_CALL(logFileParserMock, readLogFileData(::testing::_, ::testing::_)).Times(1);


    EXPECT_CALL(logDataModelMock, getLogData()).WillOnce(testing::ReturnRef(dummyLogData));

    EXPECT_CALL(logFilterViewMock, getDebugChecked()).WillOnce(::testing::Return(false));

    EXPECT_CALL(logFilterViewMock, getInfoChecked()).WillOnce(::testing::Return(false));

    EXPECT_CALL(logFilterViewMock, getWarningChecked()).WillOnce(::testing::Return(true));
    EXPECT_CALL(logViewMock, drawLogLineText(::testing::Eq(std::string_view(dummyLogLines[LogAnalyzerTool::LogLevel::Warning])), 
        LogAnalyzerTool::TextColor::Orange));

    EXPECT_CALL(logFilterViewMock, getErrorChecked()).WillOnce(::testing::Return(true));
    EXPECT_CALL(logViewMock, drawLogLineText(::testing::Eq(std::string_view(dummyLogLines[LogAnalyzerTool::LogLevel::Error])), 
        LogAnalyzerTool::TextColor::Red));

    logFilePresenter.update(filePath);
}

TEST_F(TestLogFilePresenter, test_logFilePresenter_update_error_checked) {

    EXPECT_CALL(windowFactoryMock, createChildWindow(LogAnalyzerTool::LogFilterChildWindow)).Times(1);
    EXPECT_CALL(logFilterViewMock, drawFilterCheckBoxes()).Times(1);
    EXPECT_CALL(windowFactoryMock, createChildWindow(LogAnalyzerTool::LogFileContentChildWindow)).Times(1);
    EXPECT_CALL(logFileParserMock, readLogFileData(::testing::_, ::testing::_)).Times(1);


    EXPECT_CALL(logDataModelMock, getLogData()).WillOnce(testing::ReturnRef(dummyLogData));

    EXPECT_CALL(logFilterViewMock, getDebugChecked()).WillOnce(::testing::Return(false));

    EXPECT_CALL(logFilterViewMock, getInfoChecked()).WillOnce(::testing::Return(false));

    EXPECT_CALL(logFilterViewMock, getWarningChecked()).WillOnce(::testing::Return(false));

    EXPECT_CALL(logFilterViewMock, getErrorChecked()).WillOnce(::testing::Return(true));
    EXPECT_CALL(logViewMock, drawLogLineText(::testing::Eq(std::string_view(dummyLogLines[LogAnalyzerTool::LogLevel::Error])), 
        LogAnalyzerTool::TextColor::Red));

    logFilePresenter.update(filePath);
}

}