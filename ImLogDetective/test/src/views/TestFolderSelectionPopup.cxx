#include "ImLogDetectiveDefs.h"
#include "ModalPopupFactoryMock.h"
#include "views/FolderSelectionPopup.h"
#include "TestUtility.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <fstream>
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

    void SetUp() override;
    void TearDown() override;

    StrictMock<ModalPopupFactoryMock> modalPopupFactoryMock;
    ImLogDetective::FolderSelectionPopup folderSelectionPopup;
    std::filesystem::path testFolderPath;
};


void TestFolderSelectionPopup::SetUp()
{
    testFolderPath = TestUtility::getTestDataFolder()/std::filesystem::path("TestFolderSelectionPopup");
    std::filesystem::create_directories(testFolderPath);
    std::ofstream testFileFoo(testFolderPath/"foo");
    std::ofstream testFileBar(testFolderPath/"bar");
}

void TestFolderSelectionPopup::TearDown()
{
    std::filesystem::remove_all(testFolderPath);
}

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
    EXPECT_CALL(modalPopupFactoryMock, createButton(_));
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
    EXPECT_CALL(modalPopupFactoryMock, createButton(_));
    EXPECT_CALL(modalPopupFactoryMock, endLayout());
    EXPECT_CALL(modalPopupFactoryMock, showErrorText(ErrorMessage::InvalidDirectory));

    folderSelectionPopup.drawFolderSelectionModalPopup(popupWindowPos, popupWindowSize);
}

TEST_F(TestFolderSelectionPopup, test_popupOpen_queries_modalPopupFactory) {
    
    EXPECT_CALL(modalPopupFactoryMock, isPopupOpen()).WillOnce(Return(true));
    EXPECT_TRUE(folderSelectionPopup.popupOpen());

    EXPECT_CALL(modalPopupFactoryMock, isPopupOpen()).WillOnce(Return(false));
    EXPECT_FALSE(folderSelectionPopup.popupOpen());
}

TEST_F(TestFolderSelectionPopup, test_getSelectedFolder_with_invalid_path) {

    std::string invalidFolderPath{"/foobar/bar/foo"};
    folderSelectionPopup.setInitialSelectedFolderPath(invalidFolderPath);

    auto result = folderSelectionPopup.getSelectedFolder();
    EXPECT_FALSE(result.first);
    EXPECT_TRUE(result.second.string().empty());
}

TEST_F(TestFolderSelectionPopup, test_getSelectedFolder_with_valid_path) {

    auto folderPath = testFolderPath.string();
    folderSelectionPopup.setInitialSelectedFolderPath(folderPath);

    auto result = folderSelectionPopup.getSelectedFolder();
    EXPECT_TRUE(result.first);
    EXPECT_EQ(result.second.string(), folderPath);
}

TEST_F(TestFolderSelectionPopup, test_folder_selection_popup_when_cancel_btn_clicked) {

    auto folderPath = testFolderPath.string();
    ImVec2 popupWindowSize{350.0f, 250.0f};
    ImVec2 popupWindowPos{0.0f, 0.0f};
    std::vector<PopupButton> popupButtons{PopupButton{Common::OkBtn}, PopupButton{Common::CloseBtn}};
    PopupButton clearLogBtn{SelectFolderDefs::ClearLogs};
    popupButtons[1].clicked = true;

    EXPECT_FALSE(std::filesystem::is_empty(testFolderPath));

    EXPECT_CALL(modalPopupFactoryMock, open(imvec2_equal(popupWindowPos), imvec2_equal(popupWindowSize), SelectFolderDefs::Name));
    EXPECT_CALL(modalPopupFactoryMock, beginLayout(SelectFolderDefs::Name));
    EXPECT_CALL(modalPopupFactoryMock, createInputTextBox(SelectFolderDefs::Name, _, SelectFolderDefs::TextBoxWidth))
        .WillOnce(DoAll(SetArgReferee<1>(folderPath), Return(true)));
    EXPECT_CALL(modalPopupFactoryMock, createButtonGroup(_)).WillOnce(DoAll(SetArgReferee<0>(popupButtons), Return(true)));
    EXPECT_CALL(modalPopupFactoryMock, createButton(_)).WillOnce(DoAll(SetArgReferee<0>(clearLogBtn), Return(true)));
    EXPECT_CALL(modalPopupFactoryMock, endLayout());
    EXPECT_CALL(modalPopupFactoryMock, close());

    folderSelectionPopup.drawFolderSelectionModalPopup(popupWindowPos, popupWindowSize);

    EXPECT_FALSE(std::filesystem::is_empty(testFolderPath));
}

TEST_F(TestFolderSelectionPopup, test_folder_selection_popup_when_clear_logs_btn_clicked) {

    auto folderPath = testFolderPath.string();
    folderSelectionPopup.setInitialSelectedFolderPath(folderPath);
    ImVec2 popupWindowSize{350.0f, 250.0f};
    ImVec2 popupWindowPos{0.0f, 0.0f};
    std::vector<PopupButton> popupButtons{PopupButton{Common::OkBtn}, PopupButton{Common::CloseBtn}};
    PopupButton clearLogBtn{SelectFolderDefs::ClearLogs};
    clearLogBtn.clicked = true;

    EXPECT_FALSE(std::filesystem::is_empty(testFolderPath));

    EXPECT_CALL(modalPopupFactoryMock, open(imvec2_equal(popupWindowPos), imvec2_equal(popupWindowSize), SelectFolderDefs::Name));
    EXPECT_CALL(modalPopupFactoryMock, beginLayout(SelectFolderDefs::Name));
    EXPECT_CALL(modalPopupFactoryMock, createInputTextBox(SelectFolderDefs::Name, _, SelectFolderDefs::TextBoxWidth))
        .WillOnce(DoAll(SetArgReferee<1>(folderPath), Return(true)));
    EXPECT_CALL(modalPopupFactoryMock, createButtonGroup(_)).WillOnce(DoAll(SetArgReferee<0>(popupButtons), Return(true)));
    EXPECT_CALL(modalPopupFactoryMock, createButton(_)).WillOnce(DoAll(SetArgReferee<0>(clearLogBtn), Return(true)));
    EXPECT_CALL(modalPopupFactoryMock, endLayout());
    EXPECT_CALL(modalPopupFactoryMock, close());

    folderSelectionPopup.drawFolderSelectionModalPopup(popupWindowPos, popupWindowSize);

    EXPECT_TRUE(std::filesystem::is_empty(testFolderPath));
}

}