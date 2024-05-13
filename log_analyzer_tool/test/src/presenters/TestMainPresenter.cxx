#include "ImLogDetectiveDefs.h"
#include "FileListPresenterMock.h"
#include "FolderSelectionPopupMock.h"
#include "presenters/MainPresenter.h"
#include "CopyLogsPresenterMock.h"
#include "ImGuiTextFilterWrapperMock.h"
#include "LogDataModelMock.h"
#include "LogFileParserMock.h"
#include "LogFileTabsPresenterMock.h"
#include "LogFilterViewMock.h"
#include "MainViewPortMock.h"
#include "ScopedImGuiWindowMock.h"
#include "SelectionMenuBarMock.h"
#include "TestUtility.h"
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

class TestMainPresenter : public ::testing::Test {
protected:
    ::testing::InSequence seq;

    StrictMock<MainViewPortMock> mainViewPortMock;
    StrictMock<ImGuiTextFilterWrapperMock> imGuiTextFilterWrapperMock;
    StrictMock<LogDataModelMock> logDataModelMock;
    StrictMock<LogFileParserMock> logFileParserMock;
    StrictMock<LogFilterViewMock> logFilterViewMock;
    StrictMock<FolderSelectionPopupMock> folderSelectionPopupMock;
    StrictMock<CopyLogsPresenterMock> copyLogsPresenterMock;
    StrictMock<LogFileTabsPresenterMock> logFileTabsPresenterMock;
    StrictMock<FileListPresenterMock> fileListPresenterMock;
    StrictMock<SelectionMenuBarMock> selectionMenuBarMock;
    StrictMock<ScopedImGuiWindowMock> scopedImGuiWindowMock;
    StrictMock<WindowFactoryMock> windowFactoryMock;

    void SetUp() override;

    TestMainPresenter();
    ~TestMainPresenter() = default;

    ScopedImGuiWindowMock* checkMainWindowAndMenuBarCreation(const float inputScaleFactor);
    void checkFolderMenuModal(
        const ImVec2& expectedWindowSize, 
        const ImVec2& expectedWindowPos, 
        const ImVec2& expectedPopupSize,
        bool selectFolderClicked,
        bool selectFolderPopupOpened);
    void checkCopyLogsModal(const ImVec2& expectedWindowSize, 
        const ImVec2& expectedWindowPos, 
        const ImVec2& expectedPopupSize,
        bool copyRemoteLogsClicked,
        bool copyRemoteLogsPopupOpened);
    void checkChildWindows(
        ScopedImGuiWindowMock& guiWindowMock,
        const ImVec2& mainWindowSize, 
        const ImVec2& mainWindowPos);

    std::filesystem::path testFolderPath;
    float inputScaleFactor;
    ImVec2 windowSize, windowPos, windowCenter;
    ImVec2 expectedFolderSelectionWindowPopupSize;
    ImVec2 expectedCopyLogsWindowPopupSize;
    ImLogDetective::MainPresenter mainPresenter;
};

TestMainPresenter::TestMainPresenter() :
    mainPresenter{windowFactoryMock,
        mainViewPortMock,
        selectionMenuBarMock,
        folderSelectionPopupMock,
        logFileTabsPresenterMock,
        fileListPresenterMock,
        copyLogsPresenterMock},
    testFolderPath{"/test/folder/path"},
    inputScaleFactor{0.0f}
{
}

void TestMainPresenter::SetUp()
{
    auto inputScaleFactor = 0.0f;
    windowSize = ImVec2{350.0f, 250.0f};
    windowPos = ImVec2{0.0f, 0.0f};
    windowCenter = ImVec2{175.0f, 125.0f};
    
    expectedFolderSelectionWindowPopupSize = windowSize;
    expectedFolderSelectionWindowPopupSize.x *= Bounds::SmallPopupWindowRelativeToMain_X;
    expectedFolderSelectionWindowPopupSize.y *= Bounds::SmallPopupWindowRelativeToMain_Y;

    expectedCopyLogsWindowPopupSize = windowSize;
    expectedCopyLogsWindowPopupSize.x *= Bounds::LargePopupWindowRelativeToMain_X;
    expectedCopyLogsWindowPopupSize.y *= Bounds::LargePopupWindowRelativeToMain_Y;
}

ScopedImGuiWindowMock* TestMainPresenter::checkMainWindowAndMenuBarCreation(const float inputScaleFactor)
{
    std::unique_ptr<ImLogDetective::IScopedImGuiWindow> guiWindowMock = std::make_unique<ScopedImGuiWindowMock>();
    ScopedImGuiWindowMock* guiWindowMockRef{dynamic_cast<ScopedImGuiWindowMock*>(guiWindowMock.get())};

    EXPECT_CALL(selectionMenuBarMock, getInputScaleFactor()).WillOnce(Return(inputScaleFactor));
    EXPECT_CALL(mainViewPortMock, setViewportScale(::testing::Eq(ImLogDetective::Bounds::ScaleFactorLowerBound)));
    EXPECT_CALL(windowFactoryMock, createWindow()).WillOnce(Return(ByMove(std::move(guiWindowMock))));
    EXPECT_CALL(selectionMenuBarMock, drawSelectionMenuBar());
    return guiWindowMockRef;
}

void TestMainPresenter::checkFolderMenuModal(
    const ImVec2& expectedWindowSize, 
    const ImVec2& expectedWindowPos, 
    const ImVec2& expectedPopupSize,
    bool selectFolderClicked,
    bool selectFolderPopupOpened)
{
    //Folder menu modal popup
    EXPECT_CALL(selectionMenuBarMock, selectFolderClicked()).WillOnce(Return(selectFolderClicked));
    if(selectFolderClicked)
    {
        EXPECT_CALL(mainViewPortMock, getWorkAreaSize()).WillOnce(Return(expectedWindowSize));
        EXPECT_CALL(mainViewPortMock, getViewportCenter()).WillOnce(Return(expectedWindowPos));
        EXPECT_CALL(folderSelectionPopupMock, drawFolderSelectionModalPopup(_, imvec2_equal(expectedPopupSize)));
        EXPECT_CALL(folderSelectionPopupMock, popupOpen()).WillOnce(Return(selectFolderPopupOpened));
        if(!selectFolderPopupOpened)
        {
            EXPECT_CALL(selectionMenuBarMock, selectionFolderClosed());
        }
    }
}

void TestMainPresenter::checkCopyLogsModal(const ImVec2& expectedWindowSize, 
        const ImVec2& expectedWindowPos, 
        const ImVec2& expectedPopupSize,
        bool copyRemoteLogsClicked,
        bool copyRemoteLogsPopupOpened)
{
    EXPECT_CALL(selectionMenuBarMock, copyRemoteLogsClicked()).WillOnce(Return(copyRemoteLogsClicked));

    EXPECT_CALL(mainViewPortMock, getWorkAreaSize());
    EXPECT_CALL(mainViewPortMock, getViewportCenter());
    EXPECT_CALL(copyLogsPresenterMock, update(_, _, _));
    EXPECT_CALL(copyLogsPresenterMock, isClosed()).WillOnce(Return(false));
    EXPECT_CALL(copyLogsPresenterMock, monitorCopyLogs());
}

void TestMainPresenter::checkChildWindows(
    ScopedImGuiWindowMock& guiWindowMock,
    const ImVec2& mainWindowSize, 
    const ImVec2& mainWindowPos)
{
    EXPECT_CALL(guiWindowMock, getWindowSize()).WillOnce(Return(mainWindowSize));
    EXPECT_CALL(guiWindowMock, getWindowPosition()).WillOnce(Return(mainWindowPos));
    EXPECT_CALL(windowFactoryMock, createChildWindow(WindowDefs::FileListWindow, _, _));
    EXPECT_CALL(folderSelectionPopupMock, getSelectedFolder()).WillOnce(Return(ValidFolderPath{true, testFolderPath}));
    EXPECT_CALL(fileListPresenterMock, update(::testing::Eq(testFolderPath)));
    EXPECT_CALL(guiWindowMock, onSameLine());
    EXPECT_CALL(windowFactoryMock, createChildWindow(WindowDefs::LogsWindow, _, _));
    EXPECT_CALL(fileListPresenterMock, getSelectedFiles());
    EXPECT_CALL(logFileTabsPresenterMock, update(_));
}

TEST_F(TestMainPresenter, test_MainPresenter_update_layout_creation) {

    auto guiWindowMockRef = checkMainWindowAndMenuBarCreation(inputScaleFactor);
    checkFolderMenuModal(windowSize, windowCenter, expectedFolderSelectionWindowPopupSize, false, false);
    checkCopyLogsModal(windowSize, windowCenter, expectedCopyLogsWindowPopupSize, false, false);
    checkChildWindows(*guiWindowMockRef, windowSize, windowPos);

    mainPresenter.update();
}

TEST_F(TestMainPresenter, test_MainPresenter_update_layout_creation_when_folder_selection_popup_clicked_and_opened) {

    auto guiWindowMockRef = checkMainWindowAndMenuBarCreation(inputScaleFactor);
    checkFolderMenuModal(windowSize, windowCenter, expectedFolderSelectionWindowPopupSize, true, true);
    checkCopyLogsModal(windowSize, windowCenter, expectedCopyLogsWindowPopupSize, false, false);
    checkChildWindows(*guiWindowMockRef, windowSize, windowPos);

    mainPresenter.update();
}

TEST_F(TestMainPresenter, test_MainPresenter_update_layout_creation_when_folder_selection_popup_clicked_opened_and_closed) {

    auto guiWindowMockRef = checkMainWindowAndMenuBarCreation(inputScaleFactor);
    checkFolderMenuModal(windowSize, windowCenter, expectedFolderSelectionWindowPopupSize, true, true);
    checkCopyLogsModal(windowSize, windowCenter, expectedCopyLogsWindowPopupSize, false, false);
    checkChildWindows(*guiWindowMockRef, windowSize, windowPos);

    mainPresenter.update();

    guiWindowMockRef = checkMainWindowAndMenuBarCreation(inputScaleFactor);
    checkFolderMenuModal(windowSize, windowCenter, expectedFolderSelectionWindowPopupSize, true, false);
    checkCopyLogsModal(windowSize, windowCenter, expectedCopyLogsWindowPopupSize, false, false);
    checkChildWindows(*guiWindowMockRef, windowSize, windowPos);

    mainPresenter.update();
}

}