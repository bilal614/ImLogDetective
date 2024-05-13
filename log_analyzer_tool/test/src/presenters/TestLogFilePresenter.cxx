#include "ImLogDetectiveDefs.h"
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

namespace TestImLogDetective
{

using namespace ::testing;
using ::testing::StrictMock;
using namespace ImLogDetective;

class TestLogFilePresenter : public ::testing::Test {
protected:
    ::testing::InSequence seq;

    StrictMock<EventLoopMock> eventLoopMock;
    StrictMock<ImGuiTextFilterWrapperMock> imGuiTextFilterWrapperMock;
    StrictMock<LogDataModelMock> logDataModelMock;
    StrictMock<LogFileParserMock> logFileParserMock;
    StrictMock<LogFilterViewMock> logFilterViewMock;
    StrictMock<LogViewMock> logViewMock;
    StrictMock<ScopedImGuiWindowMock> scopedImGuiWindowMock;
    StrictMock<WindowFactoryMock> windowFactoryMock;

    std::filesystem::path filePath;
    std::unordered_map<ImLogDetective::LogLevel, std::string> dummyLogLines;
    const std::vector<ImLogDetective::LogData> dummyLogData;

    TestLogFilePresenter();
    ~TestLogFilePresenter() = default;

    ImLogDetective::LogFilePresenter logFilePresenter;
};

TestLogFilePresenter::TestLogFilePresenter() :
    logFilePresenter{windowFactoryMock,
        eventLoopMock,
        logFilterViewMock,
        logViewMock,
        logFileParserMock,
        imGuiTextFilterWrapperMock},
    filePath{"/fake/path"},
    dummyLogLines{{ImLogDetective::LogLevel::Debug, "11:51:45,518 - DEBUG - Foo.Bar - foo bar"},
        {ImLogDetective::LogLevel::Info, "11:51:45,527 - INFO - Lorem.Ipsum - lorem ipsum"},
        {ImLogDetective::LogLevel::Warning, "11:51:45,718 - WARNING - Excepteur.Sint - Excepteur sint"},
        {ImLogDetective::LogLevel::Error, "11:51:46,318 - ERROR - Nemo.Enim - Nemo enim"}
        },
    dummyLogData {
        ImLogDetective::LogData{dummyLogLines[ImLogDetective::LogLevel::Debug], ImLogDetective::LogLevel::Debug},
        ImLogDetective::LogData{dummyLogLines[ImLogDetective::LogLevel::Info], ImLogDetective::LogLevel::Info},
        ImLogDetective::LogData{dummyLogLines[ImLogDetective::LogLevel::Warning], ImLogDetective::LogLevel::Warning},
        ImLogDetective::LogData{dummyLogLines[ImLogDetective::LogLevel::Error], ImLogDetective::LogLevel::Error}
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
    EXPECT_CALL(logViewMock, drawLogLineText(::testing::Eq(std::string_view(dummyLogLines[ImLogDetective::LogLevel::Debug])), 
        ImLogDetective::TextColor::White));
    
    EXPECT_CALL(imGuiTextFilterWrapperMock, passFilter(::testing::_)).WillOnce(::testing::Return(true));
    EXPECT_CALL(logFilterViewMock, getInfoChecked()).WillOnce(::testing::Return(true));
    EXPECT_CALL(logViewMock, drawLogLineText(::testing::Eq(std::string_view(dummyLogLines[ImLogDetective::LogLevel::Info])), 
        ImLogDetective::TextColor::White));

    EXPECT_CALL(imGuiTextFilterWrapperMock, passFilter(::testing::_)).WillOnce(::testing::Return(true));
    EXPECT_CALL(logFilterViewMock, getWarningChecked()).WillOnce(::testing::Return(true));
    EXPECT_CALL(logViewMock, drawLogLineText(::testing::Eq(std::string_view(dummyLogLines[ImLogDetective::LogLevel::Warning])), 
        ImLogDetective::TextColor::Orange));

    EXPECT_CALL(imGuiTextFilterWrapperMock, passFilter(::testing::_)).WillOnce(::testing::Return(true));
    EXPECT_CALL(logFilterViewMock, getErrorChecked()).WillOnce(::testing::Return(true));
    EXPECT_CALL(logViewMock, drawLogLineText(::testing::Eq(std::string_view(dummyLogLines[ImLogDetective::LogLevel::Error])), 
        ImLogDetective::TextColor::Red));

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
    EXPECT_CALL(logViewMock, drawLogLineText(::testing::Eq(std::string_view(dummyLogLines[ImLogDetective::LogLevel::Info])), 
        ImLogDetective::TextColor::White));

    EXPECT_CALL(imGuiTextFilterWrapperMock, passFilter(::testing::_)).WillOnce(::testing::Return(true));
    EXPECT_CALL(logFilterViewMock, getWarningChecked()).WillOnce(::testing::Return(true));
    EXPECT_CALL(logViewMock, drawLogLineText(::testing::Eq(std::string_view(dummyLogLines[ImLogDetective::LogLevel::Warning])), 
        ImLogDetective::TextColor::Orange));

    EXPECT_CALL(imGuiTextFilterWrapperMock, passFilter(::testing::_)).WillOnce(::testing::Return(true));
    EXPECT_CALL(logFilterViewMock, getErrorChecked()).WillOnce(::testing::Return(true));
    EXPECT_CALL(logViewMock, drawLogLineText(::testing::Eq(std::string_view(dummyLogLines[ImLogDetective::LogLevel::Error])), 
        ImLogDetective::TextColor::Red));

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
    EXPECT_CALL(logViewMock, drawLogLineText(::testing::Eq(std::string_view(dummyLogLines[ImLogDetective::LogLevel::Warning])), 
        ImLogDetective::TextColor::Orange));

    EXPECT_CALL(imGuiTextFilterWrapperMock, passFilter(::testing::_)).WillOnce(::testing::Return(true));
    EXPECT_CALL(logFilterViewMock, getErrorChecked()).WillOnce(::testing::Return(true));
    EXPECT_CALL(logViewMock, drawLogLineText(::testing::Eq(std::string_view(dummyLogLines[ImLogDetective::LogLevel::Error])), 
        ImLogDetective::TextColor::Red));

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
    EXPECT_CALL(logViewMock, drawLogLineText(::testing::Eq(std::string_view(dummyLogLines[ImLogDetective::LogLevel::Error])), 
        ImLogDetective::TextColor::Red));

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
    EXPECT_CALL(logViewMock, drawLogLineText(::testing::Eq(std::string_view(dummyLogLines[ImLogDetective::LogLevel::Debug])), 
        ImLogDetective::TextColor::White));
    
    EXPECT_CALL(imGuiTextFilterWrapperMock, passFilter(::testing::_)).WillOnce(::testing::Return(true));
    EXPECT_CALL(logFilterViewMock, getInfoChecked()).WillOnce(::testing::Return(true));
    EXPECT_CALL(logViewMock, drawLogLineText(::testing::Eq(std::string_view(dummyLogLines[ImLogDetective::LogLevel::Info])), 
        ImLogDetective::TextColor::White));

    EXPECT_CALL(imGuiTextFilterWrapperMock, passFilter(::testing::_)).WillOnce(::testing::Return(true));
    EXPECT_CALL(logFilterViewMock, getWarningChecked()).WillOnce(::testing::Return(true));
    EXPECT_CALL(logViewMock, drawLogLineText(::testing::Eq(std::string_view(dummyLogLines[ImLogDetective::LogLevel::Warning])), 
        ImLogDetective::TextColor::Orange));

    EXPECT_CALL(imGuiTextFilterWrapperMock, passFilter(::testing::_)).WillOnce(::testing::Return(true));
    EXPECT_CALL(logFilterViewMock, getErrorChecked()).WillOnce(::testing::Return(true));
    EXPECT_CALL(logViewMock, drawLogLineText(::testing::Eq(std::string_view(dummyLogLines[ImLogDetective::LogLevel::Error])), 
        ImLogDetective::TextColor::Red));

    logFilePresenter.update(filePath, false, logDataModelMock);
}

}