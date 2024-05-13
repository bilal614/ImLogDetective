#include "ImLogDetectiveDefs.h"
#include "ModalPopupFactoryMock.h"
#include "views/FolderSelectionPopup.h"
#include "TestUtility.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <memory>
#include <unordered_map>


namespace TestImLogDetective
{

using namespace ::testing;
using ::testing::StrictMock;
using namespace ImLogDetective;

class TestFolderSelectionPopup : public ::testing::Test {
protected:
    ::testing::InSequence seq;

    TestFolderSelectionPopup();
    ~TestFolderSelectionPopup() = default;

    StrictMock<ModalPopupFactoryMock> modalPopupFactoryMock;
    ImLogDetective::FolderSelectionPopup folderSelectionPopup;
};

TestFolderSelectionPopup::TestFolderSelectionPopup() :
    folderSelectionPopup{modalPopupFactoryMock}
{
}

TEST_F(TestFolderSelectionPopup, test_folder_selection_popup_is_drawn_correctly) {

    ImVec2 popupWindowSize{350.0f, 250.0f};
    ImVec2 popupWindowPos{0.0f, 0.0f};
    
    EXPECT_CALL(modalPopupFactoryMock, open(imvec2_equal(popupWindowPos), imvec2_equal(popupWindowSize), SelectFolderDefs::Name));
    EXPECT_CALL(modalPopupFactoryMock, beginLayout(SelectFolderDefs::Name));
    EXPECT_CALL(modalPopupFactoryMock, createInputTextBox(SelectFolderDefs::Name, _, SelectFolderDefs::TextBoxWidth));
    EXPECT_CALL(modalPopupFactoryMock, createButtonGroup(_));
    EXPECT_CALL(modalPopupFactoryMock, endLayout());

    folderSelectionPopup.drawFolderSelectionModalPopup(popupWindowPos, popupWindowSize);
}

TEST_F(TestFolderSelectionPopup, test_folder_selection_popup_when_invalid_directory_given_as_input_and_ok_clicked) {

    ImVec2 popupWindowSize{350.0f, 250.0f};
    ImVec2 popupWindowPos{0.0f, 0.0f};
    std::string invalidFolderPath{"/foobar/bar/foo"};
    std::vector<PopupButton> popupButtons{PopupButton{Common::OkBtn}, PopupButton{Common::CloseBtn}};
    popupButtons[0].clicked = true;

    EXPECT_CALL(modalPopupFactoryMock, open(imvec2_equal(popupWindowPos), imvec2_equal(popupWindowSize), SelectFolderDefs::Name));
    EXPECT_CALL(modalPopupFactoryMock, beginLayout(SelectFolderDefs::Name));
    EXPECT_CALL(modalPopupFactoryMock, createInputTextBox(SelectFolderDefs::Name, _, SelectFolderDefs::TextBoxWidth))
        .WillOnce(DoAll(SetArgReferee<1>(invalidFolderPath), Return(true)));
    EXPECT_CALL(modalPopupFactoryMock, createButtonGroup(_)).WillOnce(DoAll(SetArgReferee<0>(popupButtons), Return(true)));
    EXPECT_CALL(modalPopupFactoryMock, endLayout());
    EXPECT_CALL(modalPopupFactoryMock, showErrorText(ErrorMessage::InvalidDirectory));

    folderSelectionPopup.drawFolderSelectionModalPopup(popupWindowPos, popupWindowSize);
}

}