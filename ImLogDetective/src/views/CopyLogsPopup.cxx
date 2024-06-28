#include "views/CopyLogsPopup.h"
#include "ImLogDetectiveDefs.h"
#include "views/IModalPopupFactory.h"
#include "imgui.h"


namespace ImLogDetective
{

struct CopyLogsPopup::Impl
{
    Impl(IModalPopupFactory& modalPopupFactory);
    ~Impl() = default;

    void resetInternalState();

    IModalPopupFactory& modalPopupFactory;

    bool copyClicked;
    bool closeClicked;
    bool opened;
    CopyLogs copyLogsInput;
};

CopyLogsPopup::Impl::Impl(IModalPopupFactory& modalPopupFactory) :
    modalPopupFactory{modalPopupFactory},
    copyClicked{false},
    closeClicked{false},
    opened{false}
{
}

void CopyLogsPopup::Impl::resetInternalState()
{
    copyLogsInput = CopyLogs{};
    copyClicked = false;
    closeClicked = false;
    opened = false;
}

CopyLogsPopup::CopyLogsPopup(IModalPopupFactory& modalPopupFactory) :
    p{std::make_unique<Impl>(modalPopupFactory)}
{
}

CopyLogsPopup::~CopyLogsPopup() = default;

void CopyLogsPopup::open(const ImVec2& popupPosition, const ImVec2& popupSize)
{
    p->modalPopupFactory.open(popupPosition, popupSize, CopyLogsDefs::Name);
    p->opened = true;
}

void CopyLogsPopup::initInput(const CopyLogs& input)
{
    p->copyLogsInput = CopyLogs{};
    p->copyLogsInput.dstDirectory.insert(0, input.dstDirectory);
    p->copyLogsInput.srcHostPath.insert(0, input.srcHostPath);
    p->copyLogsInput.jumpHostPath1.insert(0, input.jumpHostPath1);
    p->copyLogsInput.jumpHostPath2.insert(0, input.jumpHostPath2);
    p->copyLogsInput.keyFile1.insert(0, input.keyFile1);
    p->copyLogsInput.keyFile2.insert(0, input.keyFile2);
}

void CopyLogsPopup::draw()
{
    if(p->opened)
    {
        p->modalPopupFactory.beginLayout(CopyLogsDefs::Name);

        std::vector<PopupButton> popupButtons{
            PopupButton{Common::CopyBtn},
            PopupButton{Common::CloseBtn}};
        p->modalPopupFactory.createButtonGroup(popupButtons);

        std::vector<PopupInputTextBox> popupSrcDestFolders{
            PopupInputTextBox{CopyLogsDefs::SrcHostPath, p->copyLogsInput.srcHostPath, CopyLogsDefs::TextBoxWidth},
            PopupInputTextBox{CopyLogsDefs::DestDir, p->copyLogsInput.dstDirectory, CopyLogsDefs::TextBoxWidth}};
        p->modalPopupFactory.createInputTextBoxGroup(popupSrcDestFolders, CopyLogsDefs::SrcDestGroup, true);

        std::vector<PopupInputTextBox> jumpHosts{
            PopupInputTextBox{"Jump Host 1", p->copyLogsInput.jumpHostPath1, CopyLogsDefs::TextBoxWidth},
            PopupInputTextBox{"Jump Host 2", p->copyLogsInput.jumpHostPath2, CopyLogsDefs::TextBoxWidth}};
        p->modalPopupFactory.createInputTextBoxGroup(jumpHosts, CopyLogsDefs::JumpHostGroup, false, true);

        std::vector<PopupInputTextBox> keyFiles{
            PopupInputTextBox{"Key File Path 1", p->copyLogsInput.keyFile1, CopyLogsDefs::TextBoxWidth},
            PopupInputTextBox{"Key File Path 2", p->copyLogsInput.keyFile2, CopyLogsDefs::TextBoxWidth}};
        p->modalPopupFactory.createInputTextBoxGroup(keyFiles, "Key File Paths", false, true);

        p->copyClicked = popupButtons[0].clicked;
        p->closeClicked = popupButtons[1].clicked;

        p->modalPopupFactory.endLayout();
    }
}

bool CopyLogsPopup::isOpen()
{
    return p->modalPopupFactory.isPopupOpen();
}

bool CopyLogsPopup::okBtnClicked()
{
    return p->copyClicked;
}

bool CopyLogsPopup::closeBtnClicked()
{
    return p->closeClicked;
}

void CopyLogsPopup::close()
{
    p->resetInternalState();
    p->modalPopupFactory.close();
}

CopyLogs CopyLogsPopup::getInput()
{
    return p->copyLogsInput;
}

}