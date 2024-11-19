#include "views/CopyLogsPopupImpl.h"
#include "ImLogDetectiveDefs.h"
#include "ModalPopupFactoryMock.h"
#include "ImGuiWidgetWrapperMock.h"
#include <gtest/gtest.h>
#include <cstring>
#include <memory>
#include <tuple>

namespace {

    std::string toString(const char* data)
    {
        return std::string(data, std::strlen(data));
    }

}

namespace TestImLogDetective
{

using namespace ::testing;
using ::testing::StrictMock;
using namespace ImLogDetective;

class TestCopyLogsPopup : public ::testing::Test {
protected:
    ::testing::InSequence seq;

    TestCopyLogsPopup();
    ~TestCopyLogsPopup() = default;

    StrictMock<ModalPopupFactoryMock> modalPopupFactoryMock;
    ImLogDetective::CopyLogsPopupImpl copyLogsPopup;
};

TestCopyLogsPopup::TestCopyLogsPopup() :
    copyLogsPopup{modalPopupFactoryMock}
{
}

TEST_F(TestCopyLogsPopup, test_CopyLogsPopup_copyLogsInput_contents_are_correctly_initialized) {
    
    auto expSrcHostPath{"foo/bar"};
    auto expDstDirectory{"bar/foo"};
    ImLogDetective::CopyLogs copyLogsInput{};
    copyLogsInput.getInputRef(CopyLogsDefs::RemoteHostDir) = expSrcHostPath;
    copyLogsInput.getInputRef(CopyLogsDefs::LocalDir) = expDstDirectory;

    auto input = copyLogsPopup.getInput();
    EXPECT_TRUE(toString(input.getInputRef(CopyLogsDefs::RemoteHostDir).data()).empty());
    EXPECT_TRUE(toString(input.getInputRef(CopyLogsDefs::LocalDir).data()).empty());

    copyLogsPopup.initInput(copyLogsInput);
    input = copyLogsPopup.getInput();

    EXPECT_EQ(toString(input.getInputRef(CopyLogsDefs::RemoteHostDir).data()), expSrcHostPath);
    EXPECT_EQ(toString(input.getInputRef(CopyLogsDefs::LocalDir).data()), expDstDirectory);
}

TEST_F(TestCopyLogsPopup, test_draw_CopyLogsPopup_when_CopyLogsPopup_is_open) {

    std::vector<PopupButton> popupButtons{PopupButton{Common::OkBtn}, PopupButton{Common::CloseBtn}};

    ImVec2 popupPosition{0.0f, 0.0f}, popupSize{0.0f, 0.0f};

    EXPECT_CALL(modalPopupFactoryMock, open(_, _, CopyLogsDefs::Name));
    copyLogsPopup.open(popupPosition, popupSize);

    EXPECT_CALL(modalPopupFactoryMock, beginLayout(CopyLogsDefs::Name));
    EXPECT_CALL(modalPopupFactoryMock, createButtonGroup(_)).WillOnce(DoAll(SetArgReferee<0>(popupButtons), Return(true)));
    EXPECT_CALL(modalPopupFactoryMock, createInputTextBoxGroup(_, ImLogDetective::CopyLogsDefs::RemoteHostGroup, true, _));
    EXPECT_CALL(modalPopupFactoryMock, createInputTextBoxGroup(_, Eq(CopyLogsDefs::DirectoriesGroup), _, _));
    EXPECT_CALL(modalPopupFactoryMock, createInputTextBoxGroup(_, Eq(CopyLogsDefs::JumpHostGroup), _, _));
    EXPECT_CALL(modalPopupFactoryMock, createInputTextBoxGroup(_, _, _, _));
    EXPECT_CALL(modalPopupFactoryMock, endLayout());

    copyLogsPopup.draw();
}

TEST_F(TestCopyLogsPopup, test_CopyLogsPopup_close_resets_internal_state_of_CopyLogsPopup) {

    auto expectedUser = "user";
    auto expectedIp = "127.0.0.1";
    auto expPath{"/foo/bar"};
    auto expDstDirectory{"bar/foo"};
    ImLogDetective::CopyLogs copyLogsInput{};
    copyLogsInput.getInputRef(CopyLogsDefs::RemoteHostUser) = expectedUser;
    copyLogsInput.getInputRef(CopyLogsDefs::RemoteHostIP) = expectedIp;
    copyLogsInput.getInputRef(CopyLogsDefs::RemoteHostDir) = expPath;
    copyLogsInput.getInputRef(CopyLogsDefs::LocalDir) = expDstDirectory;

    copyLogsPopup.initInput(copyLogsInput);
    auto input = copyLogsPopup.getInput();
    EXPECT_EQ(toString(input.getInputRef(CopyLogsDefs::RemoteHostUser).data()), expectedUser);
    EXPECT_EQ(toString(input.getInputRef(CopyLogsDefs::RemoteHostIP).data()), expectedIp);
    EXPECT_EQ(toString(input.getInputRef(CopyLogsDefs::RemoteHostDir).data()), expPath);
    EXPECT_EQ(toString(input.getInputRef(CopyLogsDefs::LocalDir).data()), expDstDirectory);

    EXPECT_CALL(modalPopupFactoryMock, close());
    copyLogsPopup.close();

    input = copyLogsPopup.getInput();
    EXPECT_TRUE(toString(input.getInputRef(CopyLogsDefs::RemoteHostUser).data()).empty());
    EXPECT_TRUE(toString(input.getInputRef(CopyLogsDefs::RemoteHostIP).data()).empty());
    EXPECT_TRUE(toString(input.getInputRef(CopyLogsDefs::RemoteHostDir).data()).empty());
    EXPECT_TRUE(toString(input.getInputRef(CopyLogsDefs::LocalDir).data()).empty());

    EXPECT_FALSE(copyLogsPopup.closeBtnClicked());
    EXPECT_FALSE(copyLogsPopup.okBtnClicked());
}


TEST_F(TestCopyLogsPopup, test_CopyLogsPopup_isOpen_queries_ModalPopupFactory_for_isPopupOpen) {

    EXPECT_CALL(modalPopupFactoryMock, isPopupOpen()).WillOnce(Return(true));
    EXPECT_TRUE(copyLogsPopup.isOpen());

    EXPECT_CALL(modalPopupFactoryMock, isPopupOpen()).WillOnce(Return(false));
    EXPECT_FALSE(copyLogsPopup.isOpen());
}

}