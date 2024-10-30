#include "ImLogDetectiveDefs.h"
#include "presenters/CopyLogsPresenterImpl.h"
#include "views/CopyLogsPopupImpl.h"
#include "views/ModalPopupFactory.h"
#include "views/ProtectedInputPopupImpl.h"
#include "MiniMock.h"
#include "ModalPopupFactoryMock.h"
#include "ScpExecutorMock.h"

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

class TestCopyLogsPresenterImpl : public ::testing::Test {
protected:
    ::testing::InSequence seq;

    StrictMock<MiniMock> miniMock;
    StrictMock<ModalPopupFactoryMock> modalPopupFactoryMock;
    StrictMock<ScpExecutorMock> scpExecutorMock;
    ImLogDetective::CopyLogsPopupImpl copyLogsPopup;
    ImLogDetective::ProtectedInputPopupImpl protectedInputPopupImpl;

    TestCopyLogsPresenterImpl();
    ~TestCopyLogsPresenterImpl() = default;

    ImLogDetective::CopyLogsPresenterImpl copyLogsPresenterImpl;
};

TestCopyLogsPresenterImpl::TestCopyLogsPresenterImpl() :
    copyLogsPopup{modalPopupFactoryMock},
    protectedInputPopupImpl{modalPopupFactoryMock},
    copyLogsPresenterImpl{copyLogsPopup, protectedInputPopupImpl, scpExecutorMock, miniMock}
{
}

TEST_F(TestCopyLogsPresenterImpl, test_copyLogsPresenterImpl_when_popup_is_opened) {

    ImVec2 position(0.0, 0.0);
    ImVec2 size(10.0, 10.0);

    std::vector<PopupButton> popupButtons{
            PopupButton{Common::CopyBtn},
            PopupButton{Common::CloseBtn}};

    EXPECT_CALL(miniMock, get(IniDefs::CopyLogsSection::Name, _)).Times(6);
    EXPECT_CALL(modalPopupFactoryMock, open(position, size, CopyLogsDefs::Name));
    EXPECT_CALL(modalPopupFactoryMock, beginLayout(CopyLogsDefs::Name));
    EXPECT_CALL(modalPopupFactoryMock, createButtonGroup(_));
    EXPECT_CALL(modalPopupFactoryMock, createInputTextBoxGroup(_, ImLogDetective::CopyLogsDefs::SrcDestGroup, true, _));
    EXPECT_CALL(modalPopupFactoryMock, createInputTextBoxGroup(_, CopyLogsDefs::JumpHostGroup, false, true));
    EXPECT_CALL(modalPopupFactoryMock, createInputTextBoxGroup(_, CopyLogsDefs::KeyFileGroup, false, true));
    EXPECT_CALL(modalPopupFactoryMock, endLayout());

    copyLogsPresenterImpl.update(true, position, size);
}

TEST_F(TestCopyLogsPresenterImpl, test_copyLogsPresenterImpl_when_popup_is_opened_and_close_button_was_clicked) {

    ImVec2 position(0.0, 0.0);
    ImVec2 size(10.0, 10.0);

    std::vector<PopupButton> popupButtons{
            PopupButton{Common::CopyBtn},
            PopupButton{Common::CloseBtn}};
    
    popupButtons[1].clicked = true;

    EXPECT_CALL(miniMock, get(IniDefs::CopyLogsSection::Name, _)).Times(6);
    EXPECT_CALL(modalPopupFactoryMock, open(position, size, CopyLogsDefs::Name));
    EXPECT_CALL(modalPopupFactoryMock, beginLayout(CopyLogsDefs::Name));
    EXPECT_CALL(modalPopupFactoryMock, createButtonGroup(_)).WillOnce(DoAll(SetArgReferee<0>(popupButtons), Return(true)));
    EXPECT_CALL(modalPopupFactoryMock, createInputTextBoxGroup(_, ImLogDetective::CopyLogsDefs::SrcDestGroup, true, _));
    EXPECT_CALL(modalPopupFactoryMock, createInputTextBoxGroup(_, CopyLogsDefs::JumpHostGroup, false, true));
    EXPECT_CALL(modalPopupFactoryMock, createInputTextBoxGroup(_, CopyLogsDefs::KeyFileGroup, false, true));
    EXPECT_CALL(modalPopupFactoryMock, endLayout());

    EXPECT_CALL(miniMock, updateIniFile());
    EXPECT_CALL(modalPopupFactoryMock, close());

    copyLogsPresenterImpl.update(true, position, size);
}

TEST_F(TestCopyLogsPresenterImpl, test_copyLogsPresenterImpl_when_popup_is_opened_and_copy_button_was_clicked) {

    ImVec2 position(0.0, 0.0);
    ImVec2 size(10.0, 10.0);

    std::vector<PopupButton> popupButtons{
            PopupButton{Common::CopyBtn},
            PopupButton{Common::CloseBtn}};
    
    popupButtons[0].clicked = true;

    auto expectedSrcHostPath = "foo/bar";
    copyLogsPopup.getInputRef(CopyLogsDefs::SrcHostPath) = expectedSrcHostPath;

    std::filesystem::path expectedDstDir = "bar/foo";
    copyLogsPopup.getInputRef(CopyLogsDefs::DestDir) = expectedDstDir.string();

    auto expJumpHost1 = "jump_host_1";
    copyLogsPopup.getInputRef(CopyLogsDefs::JumpHost1) = expJumpHost1;

    auto expJumpHost2 = "jump_host_2";
    copyLogsPopup.getInputRef(CopyLogsDefs::JumpHost2) = expJumpHost2;

    std::filesystem::path  expKeyFile1 = "key/file/1";
    copyLogsPopup.getInputRef(CopyLogsDefs::KeyFilePath1) = expKeyFile1.string();

    std::filesystem::path  expKeyFile2 = "key/file/2";
    copyLogsPopup.getInputRef(CopyLogsDefs::KeyFilePath2) = expKeyFile2.string();

    EXPECT_CALL(miniMock, get(IniDefs::CopyLogsSection::Name, _)).Times(6);
    EXPECT_CALL(modalPopupFactoryMock, open(position, size, CopyLogsDefs::Name));
    EXPECT_CALL(modalPopupFactoryMock, beginLayout(CopyLogsDefs::Name));
    EXPECT_CALL(modalPopupFactoryMock, createButtonGroup(_)).WillOnce(DoAll(SetArgReferee<0>(popupButtons), Return(true)));
    EXPECT_CALL(modalPopupFactoryMock, createInputTextBoxGroup(_, ImLogDetective::CopyLogsDefs::SrcDestGroup, true, _));
    EXPECT_CALL(modalPopupFactoryMock, createInputTextBoxGroup(_, CopyLogsDefs::JumpHostGroup, false, true));
    EXPECT_CALL(modalPopupFactoryMock, createInputTextBoxGroup(_, CopyLogsDefs::KeyFileGroup, false, true));
    EXPECT_CALL(modalPopupFactoryMock, endLayout());

    EXPECT_CALL(miniMock, set(IniDefs::CopyLogsSection::Name, IniDefs::CopyLogsSection::SrcHostPath, _));
    EXPECT_CALL(scpExecutorMock, setSourceRemoteHostPath(expectedSrcHostPath));

    EXPECT_CALL(miniMock, set(IniDefs::CopyLogsSection::Name, IniDefs::CopyLogsSection::DestinationPath, _));
    EXPECT_CALL(scpExecutorMock, setDestinationLocalPath(expectedDstDir));

    EXPECT_CALL(miniMock, set(IniDefs::CopyLogsSection::Name, IniDefs::CopyLogsSection::JumpHost1, _));
    EXPECT_CALL(scpExecutorMock, addJumpHost(expJumpHost1));

    EXPECT_CALL(miniMock, set(IniDefs::CopyLogsSection::Name, IniDefs::CopyLogsSection::JumpHost2, _));
    EXPECT_CALL(scpExecutorMock, addJumpHost(expJumpHost2));

    EXPECT_CALL(miniMock, set(IniDefs::CopyLogsSection::Name, IniDefs::CopyLogsSection::KeyFilePath1, _));
    EXPECT_CALL(scpExecutorMock, addIdentityFile(expKeyFile1));

    EXPECT_CALL(miniMock, set(IniDefs::CopyLogsSection::Name, IniDefs::CopyLogsSection::KeyFilePath2, _));
    EXPECT_CALL(scpExecutorMock, addIdentityFile(expKeyFile2));

    EXPECT_CALL(scpExecutorMock, download());

    EXPECT_CALL(miniMock, updateIniFile());
    EXPECT_CALL(modalPopupFactoryMock, close());

    copyLogsPresenterImpl.update(true, position, size);
}


}