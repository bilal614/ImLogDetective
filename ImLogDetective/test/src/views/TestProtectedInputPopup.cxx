#include "views/ProtectedInputPopupImpl.h"
#include "ImLogDetectiveDefs.h"
#include "ModalPopupFactoryMock.h"
#include "TestUtility.h"
#include <gtest/gtest.h>


namespace TestImLogDetective
{

using namespace ::testing;
using ::testing::StrictMock;
using namespace ImLogDetective;

class TestProtectedInputPopup : public ::testing::Test {
protected:
    ::testing::InSequence seq;

    TestProtectedInputPopup();
    ~TestProtectedInputPopup() = default;

    StrictMock<ModalPopupFactoryMock> modalPopupFactoryMock;
    ProtectedInputPopupImpl protectedInputPopup;
};

TestProtectedInputPopup::TestProtectedInputPopup() :
    protectedInputPopup{modalPopupFactoryMock}
{
}

TEST_F(TestProtectedInputPopup, test_ProtectedInputPopup_draw_method_draws_correct_ui_widget_elements_when_opened_with_given_prompt) {

    ImVec2 popupPosition{0.0f, 0.0f}, popupSize{0.0f, 0.0f};
    EXPECT_CALL(modalPopupFactoryMock, open(imvec2_equal(popupPosition), imvec2_equal(popupSize), ProtectedInputDefs::Name));
    protectedInputPopup.open(popupPosition, popupSize);

    std::string prompt = "user@127.0.01 password";
    protectedInputPopup.setPrompt(prompt);

    auto expectedPrompt = ProtectedInputDefs::Prompt + prompt;
    std::vector<PopupButton> popupButtons{PopupButton{Common::OkBtn}, PopupButton{Common::CloseBtn}};
    EXPECT_CALL(modalPopupFactoryMock, beginLayout(ProtectedInputDefs::Name));
    EXPECT_CALL(modalPopupFactoryMock, createProtectedInputTextBox(Eq(expectedPrompt), _, Eq(ProtectedInputDefs::TextBoxWidth)));
    EXPECT_CALL(modalPopupFactoryMock, createButtonGroup(_)).WillOnce(DoAll(SetArgReferee<0>(popupButtons), Return(true)));
    EXPECT_CALL(modalPopupFactoryMock, endLayout());
    protectedInputPopup.draw();
}

TEST_F(TestProtectedInputPopup, test_ProtectedInputPopup_when_close_is_called_then_popup_is_closed) {

    EXPECT_CALL(modalPopupFactoryMock, close());
    protectedInputPopup.close();

    EXPECT_CALL(modalPopupFactoryMock, isPopupOpen()).WillOnce(Return(false));
    ASSERT_FALSE(protectedInputPopup.isOpen());
    ASSERT_FALSE(protectedInputPopup.okBtnClicked());
    ASSERT_FALSE(protectedInputPopup.closeBtnClicked());
}

}