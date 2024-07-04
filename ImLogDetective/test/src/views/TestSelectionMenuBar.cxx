#include "views/SelectionMenuBarImpl.h"
#include "ImGuiMenuBarWrapperMock.h"
#include "ImLogDetectiveDefs.h"
#include <gtest/gtest.h>

namespace TestImLogDetective
{

using namespace ::testing;
using ::testing::StrictMock;
using namespace ImLogDetective;

class TestSelectionMenuBar : public ::testing::TestWithParam<std::tuple<bool, bool, bool, int>> {
protected:
    ::testing::InSequence seq;

    TestSelectionMenuBar();
    ~TestSelectionMenuBar() = default;

    StrictMock<ImGuiMenuBarWrapperMock> imGuiMenuBarWrapperMock;
    SelectionMenuBarImpl selectionMenuBar;
};

TestSelectionMenuBar::TestSelectionMenuBar() :
    selectionMenuBar{imGuiMenuBarWrapperMock}
{
}

TEST_P(TestSelectionMenuBar, test_TestLogView_drawLogLineText_draws_menu_items_correctly) {

    auto params = GetParam();
    bool selectFolderClicked = std::get<0>(params);
    bool fetchRemoteLogsClicked = std::get<1>(params);
    bool configureHighlightingClicked = std::get<2>(params);
    int scaleFactor = std::get<3>(params);
    auto expScale = std::min(Scaling::ScaleFactorLowerBound + (scaleFactor*10.0f)/100, 
        Scaling::ScaleFactorUpperBound);

    EXPECT_CALL(imGuiMenuBarWrapperMock, beginMenuBar()).WillOnce(Return(true));
    EXPECT_CALL(imGuiMenuBarWrapperMock, beginMenu(Eq(MenuBar::Name)))
        .WillOnce(Return(true));
    EXPECT_CALL(imGuiMenuBarWrapperMock, menuItem(MenuBarOptions::SelectFolder, _))
        .WillOnce(DoAll(SetArgReferee<1>(selectFolderClicked), Return(true)));
    EXPECT_CALL(imGuiMenuBarWrapperMock, menuItem(MenuBarOptions::FetchRemoteLogs, _))
        .WillOnce(DoAll(SetArgReferee<1>(fetchRemoteLogsClicked), Return(true)));
    EXPECT_CALL(imGuiMenuBarWrapperMock, menuItem(MenuBarOptions::ConfigureHiglighting, _))
        .WillOnce(DoAll(SetArgReferee<1>(configureHighlightingClicked), Return(true)));
    EXPECT_CALL(imGuiMenuBarWrapperMock, slider(Eq(MenuBar::ScaleLabel), _, _, _))
        .WillOnce(DoAll(SetArgReferee<1>(scaleFactor), Return(true)));
    EXPECT_CALL(imGuiMenuBarWrapperMock, endMenu());
    EXPECT_CALL(imGuiMenuBarWrapperMock, endMenuBar());

    selectionMenuBar.drawSelectionMenuBar();

    ASSERT_EQ(selectionMenuBar.selectFolderClicked(), selectFolderClicked);
    ASSERT_EQ(selectionMenuBar.copyRemoteLogsClicked(), fetchRemoteLogsClicked);

    ASSERT_FLOAT_EQ(selectionMenuBar.getInputScaleFactor(), 
        expScale);
}

INSTANTIATE_TEST_CASE_P(
    Draw_SelectionMenuBarTests,
    TestSelectionMenuBar,
    ::testing::Values(
        std::tuple{false, false, false, 0},
        std::tuple{true, false, false, 0},
        std::tuple{false, true, false, 1},
        std::tuple{false, false, false, 2},
        std::tuple{true, false, false, 3},
        std::tuple{true, false, false, 4},
        std::tuple{false, true, false, 5},
        std::tuple{false, false, false, 10}
    ));

class TestSelectionMenuBarClosingMenuItems : public ::testing::Test {
protected:
    ::testing::InSequence seq;

    TestSelectionMenuBarClosingMenuItems();
    ~TestSelectionMenuBarClosingMenuItems() = default;

    StrictMock<ImGuiMenuBarWrapperMock> imGuiMenuBarWrapperMock;
    SelectionMenuBarImpl selectionMenuBar;
};

TestSelectionMenuBarClosingMenuItems::TestSelectionMenuBarClosingMenuItems() :
    selectionMenuBar{imGuiMenuBarWrapperMock}
{
}

TEST_F(TestSelectionMenuBarClosingMenuItems, test_TestLogView_drawLogLineText_when_folder_selection_menu_item_is_closed) {

    bool selectFolderClicked = true;
    bool fetchRemoteLogsClicked = false;

    EXPECT_CALL(imGuiMenuBarWrapperMock, beginMenuBar()).WillOnce(Return(true));
    EXPECT_CALL(imGuiMenuBarWrapperMock, beginMenu(Eq(MenuBar::Name)))
        .WillOnce(Return(true));
    EXPECT_CALL(imGuiMenuBarWrapperMock, menuItem(MenuBarOptions::SelectFolder, _))
        .WillOnce(DoAll(SetArgReferee<1>(selectFolderClicked), Return(true)));
    EXPECT_CALL(imGuiMenuBarWrapperMock, menuItem(MenuBarOptions::FetchRemoteLogs, _))
        .WillOnce(DoAll(SetArgReferee<1>(fetchRemoteLogsClicked), Return(true)));
    EXPECT_CALL(imGuiMenuBarWrapperMock, menuItem(MenuBarOptions::ConfigureHiglighting, _));
    EXPECT_CALL(imGuiMenuBarWrapperMock, slider(Eq(MenuBar::ScaleLabel), _, _, _));
    EXPECT_CALL(imGuiMenuBarWrapperMock, endMenu());
    EXPECT_CALL(imGuiMenuBarWrapperMock, endMenuBar());

    selectionMenuBar.drawSelectionMenuBar();

    ASSERT_TRUE(selectionMenuBar.selectFolderClicked());
    ASSERT_FALSE(selectionMenuBar.copyRemoteLogsClicked());

    selectionMenuBar.selectionFolderClosed();
    ASSERT_FALSE(selectionMenuBar.selectFolderClicked());
}


TEST_F(TestSelectionMenuBarClosingMenuItems, test_TestLogView_drawLogLineText_when_copy_remote_logs_menu_item_is_closed) {

    bool selectFolderClicked = false;
    bool fetchRemoteLogsClicked = true;

    EXPECT_CALL(imGuiMenuBarWrapperMock, beginMenuBar()).WillOnce(Return(true));
    EXPECT_CALL(imGuiMenuBarWrapperMock, beginMenu(Eq(MenuBar::Name)))
        .WillOnce(Return(true));
    EXPECT_CALL(imGuiMenuBarWrapperMock, menuItem(MenuBarOptions::SelectFolder, _))
        .WillOnce(DoAll(SetArgReferee<1>(selectFolderClicked), Return(true)));
    EXPECT_CALL(imGuiMenuBarWrapperMock, menuItem(MenuBarOptions::FetchRemoteLogs, _))
        .WillOnce(DoAll(SetArgReferee<1>(fetchRemoteLogsClicked), Return(true)));
    EXPECT_CALL(imGuiMenuBarWrapperMock, menuItem(MenuBarOptions::ConfigureHiglighting, _));
    EXPECT_CALL(imGuiMenuBarWrapperMock, slider(Eq(MenuBar::ScaleLabel), _, _, _));
    EXPECT_CALL(imGuiMenuBarWrapperMock, endMenu());
    EXPECT_CALL(imGuiMenuBarWrapperMock, endMenuBar());

    selectionMenuBar.drawSelectionMenuBar();

    ASSERT_FALSE(selectionMenuBar.selectFolderClicked());
    ASSERT_TRUE(selectionMenuBar.copyRemoteLogsClicked());

    selectionMenuBar.copyRemoteLogsClosed();
    ASSERT_FALSE(selectionMenuBar.copyRemoteLogsClicked());
}

}