#include "views/CopyLogsPopupImpl.h"
#include "ImLogDetectiveDefs.h"
#include "views/ModalPopupFactory.h"
#include "imgui.h"


namespace ImLogDetective
{

struct CopyLogsPopupImpl::Impl
{
    Impl(ModalPopupFactory& modalPopupFactory);
    ~Impl() = default;

    void resetInternalState();
    bool validateInput();

    ModalPopupFactory& modalPopupFactory;

    bool copyClicked;
    bool closeClicked;
    bool opened;
    CopyLogs copyLogsInput;
};

CopyLogsPopupImpl::Impl::Impl(ModalPopupFactory& modalPopupFactory) :
    modalPopupFactory{modalPopupFactory},
    copyClicked{false},
    closeClicked{false},
    opened{false}
{
}

void CopyLogsPopupImpl::Impl::resetInternalState()
{
    copyLogsInput = CopyLogs{};
    copyClicked = false;
    closeClicked = false;
    opened = false;
}

bool CopyLogsPopupImpl::Impl::validateInput()
{
    auto inputs = copyLogsInput.getAllInputs();
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
    p{std::make_unique<Impl>(modalPopupFactory)}
{
}

CopyLogsPopupImpl::~CopyLogsPopupImpl() = default;

void CopyLogsPopupImpl::open(const ImVec2& popupPosition, const ImVec2& popupSize)
{
    p->modalPopupFactory.open(popupPosition, popupSize, CopyLogsDefs::Name);
    p->opened = true;
}

void CopyLogsPopupImpl::initInput(const CopyLogs& input)
{
    p->copyLogsInput = CopyLogs{};
    p->copyLogsInput.getInputRef(CopyLogsDefs::SrcHostPath).insert(0, input.getInputValue(CopyLogsDefs::SrcHostPath));
    p->copyLogsInput.getInputRef(CopyLogsDefs::DestDir).insert(0, input.getInputValue(CopyLogsDefs::DestDir));
    p->copyLogsInput.getInputRef(CopyLogsDefs::JumpHost1).insert(0, input.getInputValue(CopyLogsDefs::JumpHost1));
    p->copyLogsInput.getInputRef(CopyLogsDefs::JumpHost2).insert(0, input.getInputValue(CopyLogsDefs::JumpHost2));
    p->copyLogsInput.getInputRef(CopyLogsDefs::KeyFilePath1).insert(0, input.getInputValue(CopyLogsDefs::KeyFilePath1));
    p->copyLogsInput.getInputRef(CopyLogsDefs::KeyFilePath2).insert(0, input.getInputValue(CopyLogsDefs::KeyFilePath2));
}

void CopyLogsPopupImpl::draw()
{
    if(p->opened)
    {
        p->modalPopupFactory.beginLayout(CopyLogsDefs::Name);

        std::vector<PopupButton> popupButtons{
            PopupButton{Common::CopyBtn},
            PopupButton{Common::CloseBtn}};
        p->modalPopupFactory.createButtonGroup(popupButtons);

        std::vector<PopupInputTextBox> popupSrcDestFolders{
            PopupInputTextBox{CopyLogsDefs::SrcHostPath, p->copyLogsInput.getInputRef(CopyLogsDefs::SrcHostPath), CopyLogsDefs::TextBoxWidth},
            PopupInputTextBox{CopyLogsDefs::DestDir, p->copyLogsInput.getInputRef(CopyLogsDefs::DestDir), CopyLogsDefs::TextBoxWidth}};
        p->modalPopupFactory.createInputTextBoxGroup(popupSrcDestFolders, CopyLogsDefs::SrcDestGroup, true);

        std::vector<PopupInputTextBox> jumpHosts{
            PopupInputTextBox{CopyLogsDefs::JumpHost1, p->copyLogsInput.getInputRef(CopyLogsDefs::JumpHost1), CopyLogsDefs::TextBoxWidth},
            PopupInputTextBox{CopyLogsDefs::JumpHost2, p->copyLogsInput.getInputRef(CopyLogsDefs::JumpHost2), CopyLogsDefs::TextBoxWidth}};
        p->modalPopupFactory.createInputTextBoxGroup(jumpHosts, CopyLogsDefs::JumpHostGroup, false, true);

        std::vector<PopupInputTextBox> keyFiles{
            PopupInputTextBox{CopyLogsDefs::KeyFilePath1, p->copyLogsInput.getInputRef(CopyLogsDefs::KeyFilePath1), CopyLogsDefs::TextBoxWidth},
            PopupInputTextBox{CopyLogsDefs::KeyFilePath2, p->copyLogsInput.getInputRef(CopyLogsDefs::KeyFilePath2), CopyLogsDefs::TextBoxWidth}};
        p->modalPopupFactory.createInputTextBoxGroup(keyFiles, "Key File Paths", false, true);

        p->copyClicked = popupButtons[0].clicked;
        p->closeClicked = popupButtons[1].clicked;

        p->modalPopupFactory.endLayout();
    }
}

bool CopyLogsPopupImpl::isOpen()
{
    return p->modalPopupFactory.isPopupOpen();
}

bool CopyLogsPopupImpl::okBtnClicked()
{
    return p->copyClicked;
}

bool CopyLogsPopupImpl::closeBtnClicked()
{
    return p->closeClicked;
}

void CopyLogsPopupImpl::close()
{
    p->resetInternalState();
    p->modalPopupFactory.close();
}

CopyLogs CopyLogsPopupImpl::getInput()
{
    return p->copyLogsInput;
}

}