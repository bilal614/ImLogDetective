#include "LogAnalyzerToolDefs.h"
#include "FileListPresenterMock.h"
#include "FolderSelectionPopupMock.h"
#include "presenters/MainPresenter.h"
#include "ImGuiTextFilterWrapperMock.h"
#include "LogDataModelMock.h"
#include "LogFileParserMock.h"
#include "LogFileTabsPresenterMock.h"
#include "LogFilterViewMock.h"
#include "MainViewPortMock.h"
#include "ScopedImGuiWindowMock.h"
#include "SelectionMenuBarMock.h"
#include "WindowFactoryMock.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <filesystem>
#include <memory>
#include <unordered_map>

MATCHER_P(imvec2_equal, a, "") { return arg.x == a.x && arg.y == a.y; };

namespace TestLogAnalyzerTool
{

using namespace ::testing;
using ::testing::StrictMock;
using namespace LogAnalyzerTool;

class TestMainPresenter : public ::testing::Test {
protected:
    ::testing::InSequence seq;

    MainViewPortMock mainViewPortMock;
    ImGuiTextFilterWrapperMock imGuiTextFilterWrapperMock;
    LogDataModelMock logDataModelMock;
    LogFileParserMock logFileParserMock;
    LogFilterViewMock logFilterViewMock;
    FolderSelectionPopupMock folderSelectionPopupMock;
    LogFileTabsPresenterMock logFileTabsPresenterMock;
    FileListPresenterMock fileListPresenterMock;
    SelectionMenuBarMock selectionMenuBarMock;
    ScopedImGuiWindowMock scopedImGuiWindowMock;
    WindowFactoryMock windowFactoryMock;

    TestMainPresenter();
    ~TestMainPresenter() = default;

    ScopedImGuiWindowMock* checkMainWindowAndMenuBarCreation(const float inputScaleFactor);
    void checkFolderMenuModal(
        const ImVec2& expectedWindowSize, 
        const ImVec2& expectedWindowPos, 
        const ImVec2& expectedPopupSize,
        bool selectFolderClicked,
        bool popupOpened);
    void checkChildWindows(
        ScopedImGuiWindowMock& guiWindowMock,
        const ImVec2& mainWindowSize, 
        const ImVec2& mainWindowPos);

    std::filesystem::path testFolderPath;
    LogAnalyzerTool::MainPresenter mainPresenter;
};

TestMainPresenter::TestMainPresenter() :
    mainPresenter{windowFactoryMock,
        mainViewPortMock,
        selectionMenuBarMock,
        folderSelectionPopupMock,
        logFileTabsPresenterMock,
        fileListPresenterMock},
    testFolderPath{"/test/folder/path"}
{
}

ScopedImGuiWindowMock* TestMainPresenter::checkMainWindowAndMenuBarCreation(const float inputScaleFactor)
{
    std::unique_ptr<LogAnalyzerTool::IScopedImGuiWindow> guiWindowMock = std::make_unique<ScopedImGuiWindowMock>();
    ScopedImGuiWindowMock* guiWindowMockRef{dynamic_cast<ScopedImGuiWindowMock*>(guiWindowMock.get())};

    EXPECT_CALL(selectionMenuBarMock, getInputScaleFactor()).WillOnce(Return(inputScaleFactor));
    EXPECT_CALL(mainViewPortMock, setViewportScale(::testing::Eq(LogAnalyzerTool::Bounds::ScaleFactorLowerBound)));
    EXPECT_CALL(windowFactoryMock, createWindow()).WillOnce(Return(ByMove(std::move(guiWindowMock))));
    EXPECT_CALL(selectionMenuBarMock, drawSelectionMenuBar());
    return guiWindowMockRef;
}

void TestMainPresenter::checkFolderMenuModal(
    const ImVec2& expectedWindowSize, 
    const ImVec2& expectedWindowPos, 
    const ImVec2& expectedPopupSize,
    bool selectFolderClicked,
    bool popupOpened)
{
    //Folder menu modal popup
    EXPECT_CALL(selectionMenuBarMock, selectFolderClicked()).WillOnce(Return(selectFolderClicked));
    EXPECT_CALL(mainViewPortMock, getWorkAreaSize()).WillOnce(Return(expectedWindowSize));
    EXPECT_CALL(mainViewPortMock, getViewportCenter()).WillOnce(Return(expectedWindowPos));
    EXPECT_CALL(folderSelectionPopupMock, drawFolderSelectionModalPopup(_, imvec2_equal(expectedPopupSize)));
    EXPECT_CALL(folderSelectionPopupMock, popupOpen()).WillOnce(Return(popupOpened));
    if(!popupOpened)
    {
        EXPECT_CALL(selectionMenuBarMock, selectionFolderClosed());
    }
}

void TestMainPresenter::checkChildWindows(
    ScopedImGuiWindowMock& guiWindowMock,
    const ImVec2& mainWindowSize, 
    const ImVec2& mainWindowPos)
{
    EXPECT_CALL(guiWindowMock, getWindowSize()).WillOnce(Return(mainWindowSize));
    EXPECT_CALL(guiWindowMock, getWindowPosition()).WillOnce(Return(mainWindowPos));
    EXPECT_CALL(windowFactoryMock, createChildWindow(WindowDefs::FileListWindow, _, _));
    EXPECT_CALL(folderSelectionPopupMock, getSelectedFolder()).WillOnce(Return(testFolderPath));
    EXPECT_CALL(fileListPresenterMock, update(::testing::Eq(testFolderPath)));
    EXPECT_CALL(guiWindowMock, onSameLine());
    EXPECT_CALL(windowFactoryMock, createChildWindow(WindowDefs::LogsWindow, _, _));
    EXPECT_CALL(fileListPresenterMock, getSelectedFiles());
    EXPECT_CALL(logFileTabsPresenterMock, update(_));
}

TEST_F(TestMainPresenter, test_MainPresenter_update_layout_creation) {

    //TODO: Use same default InputScaleFactor
    auto inputScaleFactor = 0.0f;
    ImVec2 windowSize{350.0f, 250.0f};
    ImVec2 windowPos{0.0f, 0.0f};

    auto guiWindowMockRef = checkMainWindowAndMenuBarCreation(inputScaleFactor);
    EXPECT_CALL(selectionMenuBarMock, selectFolderClicked()).WillOnce(Return(false));
    checkChildWindows(*guiWindowMockRef, windowSize, windowPos);

    mainPresenter.update();
}

TEST_F(TestMainPresenter, test_MainPresenter_update_layout_creation_when_folder_selection_popup_clicked_and_opened) {

    //TODO: Use same default InputScaleFactor
    auto inputScaleFactor = 0.0f;
    ImVec2 windowSize{350.0f, 250.0f};
    ImVec2 windowPos{0.0f, 0.0f};
    ImVec2 windowCenter{175.0f, 125.0f};
    auto expectedPopupSize = windowSize;
    expectedPopupSize.x *= Bounds::PopupWindowRelativeToMain_X;
    expectedPopupSize.y *= Bounds::PopupWindowRelativeToMain_Y;

    auto guiWindowMockRef = checkMainWindowAndMenuBarCreation(inputScaleFactor);
    checkFolderMenuModal(windowSize, windowCenter, expectedPopupSize, true, true);
    checkChildWindows(*guiWindowMockRef, windowSize, windowPos);

    mainPresenter.update();
}

TEST_F(TestMainPresenter, test_MainPresenter_update_layout_creation_when_folder_selection_popup_clicked_opened_and_closed) {

    //TODO: Use same default InputScaleFactor
    auto inputScaleFactor = 0.0f;
    ImVec2 windowSize{350.0f, 250.0f};
    ImVec2 windowPos{0.0f, 0.0f};
    ImVec2 windowCenter{175.0f, 125.0f};
    auto expectedPopupSize = windowSize;
    expectedPopupSize.x *= Bounds::PopupWindowRelativeToMain_X;
    expectedPopupSize.y *= Bounds::PopupWindowRelativeToMain_Y;

    auto guiWindowMockRef = checkMainWindowAndMenuBarCreation(inputScaleFactor);
    checkFolderMenuModal(windowSize, windowCenter, expectedPopupSize, true, true);
    checkChildWindows(*guiWindowMockRef, windowSize, windowPos);

    mainPresenter.update();

    guiWindowMockRef = checkMainWindowAndMenuBarCreation(inputScaleFactor);
    checkFolderMenuModal(windowSize, windowCenter, expectedPopupSize, true, false);
    checkChildWindows(*guiWindowMockRef, windowSize, windowPos);

    mainPresenter.update();
}

}