#include "views/CopyLogsPopupImpl.h"
#include "ImLogDetectiveDefs.h"
#include "views/ModalPopupFactory.h"
#include "imgui.h"


namespace ImLogDetective
{


void CopyLogsPopupImpl::resetInternalState()
{
    initInput(CopyLogs{});
    copyClicked = false;
    closeClicked = false;
    opened = false;
}

bool CopyLogsPopupImpl::validateInput()
{
    auto inputs = getAllInputs();
    for(const auto& input : inputs)
    {
        if(input.find_first_not_of('\0') == std::string::npos)
        {
            return false;
        }
    }
    return true;
}

CopyLogsPopupImpl::CopyLogsPopupImpl(ModalPopupFactory& modalPopupFactory) :
    modalPopupFactory{modalPopupFactory},
    copyClicked{false},
    closeClicked{false},
    opened{false}
{
}

CopyLogsPopupImpl::~CopyLogsPopupImpl() = default;

void CopyLogsPopupImpl::open(const ImVec2& popupPosition, const ImVec2& popupSize)
{
    modalPopupFactory.open(popupPosition, popupSize, CopyLogsDefs::Name);
    opened = true;
}

void CopyLogsPopupImpl::draw()
{
    if(opened)
    {
        modalPopupFactory.beginLayout(CopyLogsDefs::Name);

        std::vector<PopupButton> buttons{
            PopupButton{Common::CopyBtn},
            PopupButton{Common::CloseBtn}};
        modalPopupFactory.createButtonGroup(buttons);

        std::vector<PopupInputTextBox> remoteHost{
            PopupInputTextBox{CopyLogsDefs::RemoteHostIP, getInputRef(CopyLogsDefs::RemoteHostIP), CopyLogsDefs::TextBoxWidth},
            PopupInputTextBox{CopyLogsDefs::RemoteHostUser, getInputRef(CopyLogsDefs::RemoteHostUser), CopyLogsDefs::TextBoxWidth}};
        modalPopupFactory.createInputTextBoxGroup(remoteHost, CopyLogsDefs::RemoteHostGroup, true);

        std::vector<PopupInputTextBox> srcDestFolders{
            PopupInputTextBox{CopyLogsDefs::RemoteHostDir, getInputRef(CopyLogsDefs::RemoteHostDir), CopyLogsDefs::TextBoxWidth},
            PopupInputTextBox{CopyLogsDefs::LocalDir, getInputRef(CopyLogsDefs::LocalDir), CopyLogsDefs::TextBoxWidth}};
        modalPopupFactory.createInputTextBoxGroup(srcDestFolders, CopyLogsDefs::DirectoriesGroup, true);

        std::vector<PopupInputTextBox> jumpHosts{
            PopupInputTextBox{CopyLogsDefs::JumpHost1, getInputRef(CopyLogsDefs::JumpHost1), CopyLogsDefs::TextBoxWidth},
            PopupInputTextBox{CopyLogsDefs::JumpHost2, getInputRef(CopyLogsDefs::JumpHost2), CopyLogsDefs::TextBoxWidth}};
        modalPopupFactory.createInputTextBoxGroup(jumpHosts, CopyLogsDefs::JumpHostGroup, false, true);

        std::vector<PopupInputTextBox> keyFiles{
            PopupInputTextBox{CopyLogsDefs::KeyFilePath1, getInputRef(CopyLogsDefs::KeyFilePath1), CopyLogsDefs::TextBoxWidth},
            PopupInputTextBox{CopyLogsDefs::KeyFilePath2, getInputRef(CopyLogsDefs::KeyFilePath2), CopyLogsDefs::TextBoxWidth}};
        modalPopupFactory.createInputTextBoxGroup(keyFiles, CopyLogsDefs::KeyFileGroup, false, true);

        copyClicked = buttons[0].clicked;
        closeClicked = buttons[1].clicked;

        modalPopupFactory.endLayout();
    }
}

bool CopyLogsPopupImpl::isOpen()
{
    return modalPopupFactory.isPopupOpen();
}

bool CopyLogsPopupImpl::okBtnClicked()
{
    return copyClicked;
}

bool CopyLogsPopupImpl::closeBtnClicked()
{
    return closeClicked;
}

void CopyLogsPopupImpl::close()
{
    resetInternalState();
    modalPopupFactory.close();
}

CopyLogs CopyLogsPopupImpl::getInput()
{
    return copyLogsInput;
}

}