#include "LogAnalyzerToolDefs.h"
#include "presenters/LogFilePresenter.h"
#include "EventLoopMock.h"
#include "ImGuiTextFilterWrapperMock.h"
#include "LogDataModelMock.h"
#include "LogFileParserMock.h"
#include "LogFilterViewMock.h"
#include "LogViewMock.h"
#include "ScopedImGuiWindowMock.h"
#include "WindowFactoryMock.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <filesystem>
#include <memory>
#include <unordered_map>

namespace TestLogAnalyzerTool
{

using namespace ::testing;
using ::testing::StrictMock;
using namespace LogAnalyzerTool;

class TestLogFilePresenter : public ::testing::Test {
protected:
    ::testing::InSequence seq;

    EventLoopMock eventLoopMock;
    ImGuiTextFilterWrapperMock imGuiTextFilterWrapperMock;
    LogDataModelMock logDataModelMock;
    LogFileParserMock logFileParserMock;
    LogFilterViewMock logFilterViewMock;
    LogViewMock logViewMock;
    ScopedImGuiWindowMock scopedImGuiWindowMock;
    WindowFactoryMock windowFactoryMock;

    std::filesystem::path filePath;
    std::unordered_map<LogAnalyzerTool::LogLevel, std::string> dummyLogLines;
    const std::vector<LogAnalyzerTool::LogData> dummyLogData;

    TestLogFilePresenter();
    ~TestLogFilePresenter() = default;

    LogAnalyzerTool::LogFilePresenter logFilePresenter;
};

TestLogFilePresenter::TestLogFilePresenter() :
    logFilePresenter{windowFactoryMock,
        eventLoopMock,
        logFilterViewMock,
        logViewMock,
        logFileParserMock,
        imGuiTextFilterWrapperMock},
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

TEST_F(TestLogFilePresenter, test_logFilePresenter_update_debug_info_warning_error_checked) {

    std::function<void()> postedReadDataFunction;

    EXPECT_CALL(windowFactoryMock, createChildWindow(WindowDefs::LogFilterChildWindow, ::testing::_, ::testing::_)).Times(1);
    EXPECT_CALL(logFilterViewMock, drawFilterCheckBoxes()).Times(1);
    EXPECT_CALL(windowFactoryMock, createChildWindow(WindowDefs::LogFileContentChildWindow, ::testing::_, ::testing::_)).Times(1);
    EXPECT_CALL(eventLoopMock, post(::testing::An<const std::function<void()>&>())).WillOnce(DoAll(::testing::SaveArg<0>(&postedReadDataFunction)));

    EXPECT_CALL(logDataModelMock, getLogData()).WillOnce(testing::ReturnRef(dummyLogData));
    
    EXPECT_CALL(imGuiTextFilterWrapperMock, passFilter(::testing::_)).WillOnce(::testing::Return(true));
    EXPECT_CALL(logFilterViewMock, getDebugChecked()).WillOnce(::testing::Return(true));
    EXPECT_CALL(logViewMock, drawLogLineText(::testing::Eq(std::string_view(dummyLogLines[LogAnalyzerTool::LogLevel::Debug])), 
        LogAnalyzerTool::TextColor::White));
    
    EXPECT_CALL(imGuiTextFilterWrapperMock, passFilter(::testing::_)).WillOnce(::testing::Return(true));
    EXPECT_CALL(logFilterViewMock, getInfoChecked()).WillOnce(::testing::Return(true));
    EXPECT_CALL(logViewMock, drawLogLineText(::testing::Eq(std::string_view(dummyLogLines[LogAnalyzerTool::LogLevel::Info])), 
        LogAnalyzerTool::TextColor::White));

    EXPECT_CALL(imGuiTextFilterWrapperMock, passFilter(::testing::_)).WillOnce(::testing::Return(true));
    EXPECT_CALL(logFilterViewMock, getWarningChecked()).WillOnce(::testing::Return(true));
    EXPECT_CALL(logViewMock, drawLogLineText(::testing::Eq(std::string_view(dummyLogLines[LogAnalyzerTool::LogLevel::Warning])), 
        LogAnalyzerTool::TextColor::Orange));

    EXPECT_CALL(imGuiTextFilterWrapperMock, passFilter(::testing::_)).WillOnce(::testing::Return(true));
    EXPECT_CALL(logFilterViewMock, getErrorChecked()).WillOnce(::testing::Return(true));
    EXPECT_CALL(logViewMock, drawLogLineText(::testing::Eq(std::string_view(dummyLogLines[LogAnalyzerTool::LogLevel::Error])), 
        LogAnalyzerTool::TextColor::Red));

    logFilePresenter.update(filePath, true, logDataModelMock);

    EXPECT_CALL(logFileParserMock, readLogFileData(::testing::_, ::testing::_)).Times(1);
    postedReadDataFunction();
}

TEST_F(TestLogFilePresenter, test_logFilePresenter_update_info_warning_error_checked) {

    std::function<void()> postedReadDataFunction;

    EXPECT_CALL(windowFactoryMock, createChildWindow(WindowDefs::LogFilterChildWindow, ::testing::_, ::testing::_)).Times(1);
    EXPECT_CALL(logFilterViewMock, drawFilterCheckBoxes()).Times(1);
    EXPECT_CALL(windowFactoryMock, createChildWindow(WindowDefs::LogFileContentChildWindow, ::testing::_, ::testing::_)).Times(1);
    EXPECT_CALL(eventLoopMock, post(::testing::An<const std::function<void()>&>())).WillOnce(DoAll(::testing::SaveArg<0>(&postedReadDataFunction)));

    EXPECT_CALL(logDataModelMock, getLogData()).WillOnce(testing::ReturnRef(dummyLogData));

    EXPECT_CALL(imGuiTextFilterWrapperMock, passFilter(::testing::_)).WillOnce(::testing::Return(true));
    EXPECT_CALL(logFilterViewMock, getDebugChecked()).WillOnce(::testing::Return(false));

    EXPECT_CALL(imGuiTextFilterWrapperMock, passFilter(::testing::_)).WillOnce(::testing::Return(true));
    EXPECT_CALL(logFilterViewMock, getInfoChecked()).WillOnce(::testing::Return(true));
    EXPECT_CALL(logViewMock, drawLogLineText(::testing::Eq(std::string_view(dummyLogLines[LogAnalyzerTool::LogLevel::Info])), 
        LogAnalyzerTool::TextColor::White));

    EXPECT_CALL(imGuiTextFilterWrapperMock, passFilter(::testing::_)).WillOnce(::testing::Return(true));
    EXPECT_CALL(logFilterViewMock, getWarningChecked()).WillOnce(::testing::Return(true));
    EXPECT_CALL(logViewMock, drawLogLineText(::testing::Eq(std::string_view(dummyLogLines[LogAnalyzerTool::LogLevel::Warning])), 
        LogAnalyzerTool::TextColor::Orange));

    EXPECT_CALL(imGuiTextFilterWrapperMock, passFilter(::testing::_)).WillOnce(::testing::Return(true));
    EXPECT_CALL(logFilterViewMock, getErrorChecked()).WillOnce(::testing::Return(true));
    EXPECT_CALL(logViewMock, drawLogLineText(::testing::Eq(std::string_view(dummyLogLines[LogAnalyzerTool::LogLevel::Error])), 
        LogAnalyzerTool::TextColor::Red));

    logFilePresenter.update(filePath, true, logDataModelMock);

    EXPECT_CALL(logFileParserMock, readLogFileData(::testing::_, ::testing::_)).Times(1);
    postedReadDataFunction();
}

TEST_F(TestLogFilePresenter, test_logFilePresenter_update_warning_error_checked) {

    std::function<void()> postedReadDataFunction;

    EXPECT_CALL(windowFactoryMock, createChildWindow(WindowDefs::LogFilterChildWindow, ::testing::_, ::testing::_)).Times(1);
    EXPECT_CALL(logFilterViewMock, drawFilterCheckBoxes()).Times(1);
    EXPECT_CALL(windowFactoryMock, createChildWindow(WindowDefs::LogFileContentChildWindow, ::testing::_, ::testing::_)).Times(1);
    EXPECT_CALL(eventLoopMock, post(::testing::An<const std::function<void()>&>())).WillOnce(DoAll(::testing::SaveArg<0>(&postedReadDataFunction)));

    EXPECT_CALL(logDataModelMock, getLogData()).WillOnce(testing::ReturnRef(dummyLogData));

    EXPECT_CALL(imGuiTextFilterWrapperMock, passFilter(::testing::_)).WillOnce(::testing::Return(true));
    EXPECT_CALL(logFilterViewMock, getDebugChecked()).WillOnce(::testing::Return(false));

    EXPECT_CALL(imGuiTextFilterWrapperMock, passFilter(::testing::_)).WillOnce(::testing::Return(true));
    EXPECT_CALL(logFilterViewMock, getInfoChecked()).WillOnce(::testing::Return(false));

    EXPECT_CALL(imGuiTextFilterWrapperMock, passFilter(::testing::_)).WillOnce(::testing::Return(true));
    EXPECT_CALL(logFilterViewMock, getWarningChecked()).WillOnce(::testing::Return(true));
    EXPECT_CALL(logViewMock, drawLogLineText(::testing::Eq(std::string_view(dummyLogLines[LogAnalyzerTool::LogLevel::Warning])), 
        LogAnalyzerTool::TextColor::Orange));

    EXPECT_CALL(imGuiTextFilterWrapperMock, passFilter(::testing::_)).WillOnce(::testing::Return(true));
    EXPECT_CALL(logFilterViewMock, getErrorChecked()).WillOnce(::testing::Return(true));
    EXPECT_CALL(logViewMock, drawLogLineText(::testing::Eq(std::string_view(dummyLogLines[LogAnalyzerTool::LogLevel::Error])), 
        LogAnalyzerTool::TextColor::Red));

    logFilePresenter.update(filePath, true, logDataModelMock);

    EXPECT_CALL(logFileParserMock, readLogFileData(::testing::_, ::testing::_)).Times(1);
    postedReadDataFunction();
}

TEST_F(TestLogFilePresenter, test_logFilePresenter_update_error_checked) {

    std::function<void()> postedReadDataFunction;

    EXPECT_CALL(windowFactoryMock, createChildWindow(WindowDefs::LogFilterChildWindow, ::testing::_, ::testing::_)).Times(1);
    EXPECT_CALL(logFilterViewMock, drawFilterCheckBoxes()).Times(1);
    EXPECT_CALL(windowFactoryMock, createChildWindow(WindowDefs::LogFileContentChildWindow, ::testing::_, ::testing::_)).Times(1);
    EXPECT_CALL(eventLoopMock, post(::testing::An<const std::function<void()>&>())).WillOnce(DoAll(::testing::SaveArg<0>(&postedReadDataFunction)));

    EXPECT_CALL(logDataModelMock, getLogData()).WillOnce(testing::ReturnRef(dummyLogData));

    EXPECT_CALL(imGuiTextFilterWrapperMock, passFilter(::testing::_)).WillOnce(::testing::Return(true));
    EXPECT_CALL(logFilterViewMock, getDebugChecked()).WillOnce(::testing::Return(false));

    EXPECT_CALL(imGuiTextFilterWrapperMock, passFilter(::testing::_)).WillOnce(::testing::Return(true));
    EXPECT_CALL(logFilterViewMock, getInfoChecked()).WillOnce(::testing::Return(false));

    EXPECT_CALL(imGuiTextFilterWrapperMock, passFilter(::testing::_)).WillOnce(::testing::Return(true));
    EXPECT_CALL(logFilterViewMock, getWarningChecked()).WillOnce(::testing::Return(false));

    EXPECT_CALL(imGuiTextFilterWrapperMock, passFilter(::testing::_)).WillOnce(::testing::Return(true));
    EXPECT_CALL(logFilterViewMock, getErrorChecked()).WillOnce(::testing::Return(true));
    EXPECT_CALL(logViewMock, drawLogLineText(::testing::Eq(std::string_view(dummyLogLines[LogAnalyzerTool::LogLevel::Error])), 
        LogAnalyzerTool::TextColor::Red));

    logFilePresenter.update(filePath, true, logDataModelMock);

    EXPECT_CALL(logFileParserMock, readLogFileData(::testing::_, ::testing::_)).Times(1);
    postedReadDataFunction();
}

TEST_F(TestLogFilePresenter, test_logFilePresenter_update_debug_info_warning_error_checked_reading_log_file_off) {

    EXPECT_CALL(windowFactoryMock, createChildWindow(WindowDefs::LogFilterChildWindow, ::testing::_, ::testing::_)).Times(1);
    EXPECT_CALL(logFilterViewMock, drawFilterCheckBoxes()).Times(1);
    EXPECT_CALL(windowFactoryMock, createChildWindow(WindowDefs::LogFileContentChildWindow, ::testing::_, ::testing::_)).Times(1);

    EXPECT_CALL(logDataModelMock, getLogData()).WillOnce(testing::ReturnRef(dummyLogData));
    
    EXPECT_CALL(imGuiTextFilterWrapperMock, passFilter(::testing::_)).WillOnce(::testing::Return(true));
    EXPECT_CALL(logFilterViewMock, getDebugChecked()).WillOnce(::testing::Return(true));
    EXPECT_CALL(logViewMock, drawLogLineText(::testing::Eq(std::string_view(dummyLogLines[LogAnalyzerTool::LogLevel::Debug])), 
        LogAnalyzerTool::TextColor::White));
    
    EXPECT_CALL(imGuiTextFilterWrapperMock, passFilter(::testing::_)).WillOnce(::testing::Return(true));
    EXPECT_CALL(logFilterViewMock, getInfoChecked()).WillOnce(::testing::Return(true));
    EXPECT_CALL(logViewMock, drawLogLineText(::testing::Eq(std::string_view(dummyLogLines[LogAnalyzerTool::LogLevel::Info])), 
        LogAnalyzerTool::TextColor::White));

    EXPECT_CALL(imGuiTextFilterWrapperMock, passFilter(::testing::_)).WillOnce(::testing::Return(true));
    EXPECT_CALL(logFilterViewMock, getWarningChecked()).WillOnce(::testing::Return(true));
    EXPECT_CALL(logViewMock, drawLogLineText(::testing::Eq(std::string_view(dummyLogLines[LogAnalyzerTool::LogLevel::Warning])), 
        LogAnalyzerTool::TextColor::Orange));

    EXPECT_CALL(imGuiTextFilterWrapperMock, passFilter(::testing::_)).WillOnce(::testing::Return(true));
    EXPECT_CALL(logFilterViewMock, getErrorChecked()).WillOnce(::testing::Return(true));
    EXPECT_CALL(logViewMock, drawLogLineText(::testing::Eq(std::string_view(dummyLogLines[LogAnalyzerTool::LogLevel::Error])), 
        LogAnalyzerTool::TextColor::Red));

    logFilePresenter.update(filePath, false, logDataModelMock);
}

}