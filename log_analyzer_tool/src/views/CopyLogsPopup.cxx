#include "views/CopyLogsPopup.h"
#include "dearimgui/IModalPopupFactory.h"
#include "LogAnalyzerToolDefs.h"
#include <cstring>
#include <filesystem>

#include "imgui.h"

namespace {

    std::string toString(const char* data)
    {
        return std::string(data, std::strlen(data));
    }
}

namespace LogAnalyzerTool
{

struct CopyLogsPopup::Impl
{
    Impl(IModalPopupFactory& modalPopupFactory);
    ~Impl() = default;
    void processPopupInput(
        bool copyButtonClicked, 
        bool closeButtonClicked);

    IModalPopupFactory& modalPopupFactory;
};

CopyLogsPopup::Impl::Impl(IModalPopupFactory& modalPopupFactory) :
    modalPopupFactory{modalPopupFactory}
{
}

void CopyLogsPopup::Impl::processPopupInput(bool copyButtonClicked, bool closeButtonClicked)
{
    if (closeButtonClicked)
    {
        modalPopupFactory.close();
        return;
    }
    if(copyButtonClicked)
    { 
        modalPopupFactory.close();
        return;
    }
}

CopyLogsPopup::CopyLogsPopup(IModalPopupFactory& modalPopupFactory) :
    p{std::make_unique<Impl>(modalPopupFactory)}
{
}

CopyLogsPopup::~CopyLogsPopup() = default;

void CopyLogsPopup::drawCopyLogsPopup(ImVec2 popupPosition, ImVec2 popupSize)
{
    p->modalPopupFactory.open(popupPosition, popupSize, CopyLogsDefs::Name);
    p->modalPopupFactory.beginLayout(CopyLogsDefs::Name);

    std::vector<PopupButton> popupButtons = {PopupButton{CopyLogsDefs::CopyBtn}, PopupButton{CopyLogsDefs::CloseBtn}};
    p->modalPopupFactory.createButtonGroup(popupButtons);

    std::vector<PopupInputTextBox> popupSrcDestFolders = {PopupInputTextBox{"Source Directory", CopyLogsDefs::TextBoxWidth}, 
        PopupInputTextBox{"Destination Directory", CopyLogsDefs::TextBoxWidth}}; 
    p->modalPopupFactory.createInputTextBoxGroup(popupSrcDestFolders, "Directories", true);

    std::vector<PopupInputTextBox> jumpHosts = {PopupInputTextBox{"Jump Host 1", CopyLogsDefs::TextBoxWidth},
        PopupInputTextBox{"Jump Host 2", CopyLogsDefs::TextBoxWidth}};
    p->modalPopupFactory.createInputTextBoxGroup(jumpHosts, "Jump Hosts", false, true);

    p->processPopupInput(popupButtons[0].clicked, popupButtons[1].clicked);

    p->modalPopupFactory.endLayout();
}

bool CopyLogsPopup::popupOpen()
{
    return p->modalPopupFactory.isPopupOpen();
}

}