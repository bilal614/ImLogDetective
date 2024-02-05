#include "LogAnalyzerToolDefs.h"
#include "ModalPopupFactoryMock.h"
#include "views/FolderSelectionPopup.h"
#include "TestUtility.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <memory>
#include <unordered_map>


namespace TestLogAnalyzerTool
{

using namespace ::testing;
using ::testing::StrictMock;
using namespace LogAnalyzerTool;

class TestFolderSelectionPopup : public ::testing::Test {
protected:
    ::testing::InSequence seq;

    TestFolderSelectionPopup();
    ~TestFolderSelectionPopup() = default;

    ModalPopupFactoryMock modalPopupFactoryMock;
    LogAnalyzerTool::FolderSelectionPopup folderSelectionPopup;
};

TestFolderSelectionPopup::TestFolderSelectionPopup() :
    folderSelectionPopup{modalPopupFactoryMock}
{
}

TEST_F(TestFolderSelectionPopup, test_folder_selection_popup_is_drawn_correctly) {

    ImVec2 popupWindowSize{350.0f, 250.0f};
    ImVec2 popupWindowPos{0.0f, 0.0f};
    
    EXPECT_CALL(modalPopupFactoryMock, open(imvec2_equal(popupWindowPos), imvec2_equal(popupWindowSize), SelectFolderPopup::Name));
    EXPECT_CALL(modalPopupFactoryMock, beginLayout(SelectFolderPopup::Name));
    EXPECT_CALL(modalPopupFactoryMock, createInputTextBox(SelectFolderPopup::Name, _));
    EXPECT_CALL(modalPopupFactoryMock, createButtonGroup(_));
    EXPECT_CALL(modalPopupFactoryMock, endLayout());

    folderSelectionPopup.drawFolderSelectionModalPopup(popupWindowPos, popupWindowSize);
}

TEST_F(TestFolderSelectionPopup, test_folder_selection_popup_when_invalid_directory_given_as_input_and_ok_clicked) {

    ImVec2 popupWindowSize{350.0f, 250.0f};
    ImVec2 popupWindowPos{0.0f, 0.0f};
    std::string invalidFolderPath{"/foobar/bar/foo"};
    std::vector<PopupButton> popupButtons{PopupButton{SelectFolderPopup::OkBtn}, PopupButton{SelectFolderPopup::CloseBtn}};
    popupButtons[0].clicked = true;

    EXPECT_CALL(modalPopupFactoryMock, open(imvec2_equal(popupWindowPos), imvec2_equal(popupWindowSize), SelectFolderPopup::Name));
    EXPECT_CALL(modalPopupFactoryMock, beginLayout(SelectFolderPopup::Name));
    EXPECT_CALL(modalPopupFactoryMock, createInputTextBox(SelectFolderPopup::Name, _)).WillOnce(DoAll(SetArgReferee<1>(invalidFolderPath), Return(true)));
    EXPECT_CALL(modalPopupFactoryMock, createButtonGroup(_)).WillOnce(DoAll(SetArgReferee<0>(popupButtons), Return(true)));
    EXPECT_CALL(modalPopupFactoryMock, showErrorText(ErrorMessage::InvalidDirectory));
    EXPECT_CALL(modalPopupFactoryMock, endLayout());

    folderSelectionPopup.drawFolderSelectionModalPopup(popupWindowPos, popupWindowSize);
}

}