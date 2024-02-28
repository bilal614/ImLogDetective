#include "views/CopyLogsPopup.h"
#include "views/IModalPopupFactory.h"
#include "LogAnalyzerToolDefs.h"
#include "event_handling/IEventLoop.h"
#include <cstring>
#include <filesystem>

#include "IPtyMaster.h"
#include "PtyMaster.h"

#include "imgui.h"

namespace {

    std::string toString(const char* data)
    {
        return std::string(data, std::strlen(data));
    }

    struct CopyLogs{
        std::string srcHostPath;
        std::string dstDirectory;
        std::string jumpHostPath1;
        std::string jumpHostPath2;
        std::string jumpHostPath3;

        std::filesystem::path identity_file_1;
        std::filesystem::path identity_file_2;
    };
}

namespace LogAnalyzerTool
{

struct CopyLogsPopup::Impl
{
    Impl(IModalPopupFactory& modalPopupFactory, LogEventHandling::IEventLoop& eventLoop);
    ~Impl() = default;
    void processPopupInput(
        bool copyButtonClicked, 
        bool closeButtonClicked,
        const CopyLogs& copyLogs);

    IModalPopupFactory& modalPopupFactory;
    LogEventHandling::IEventLoop& eventLoop;
};

CopyLogsPopup::Impl::Impl(IModalPopupFactory& modalPopupFactory, LogEventHandling::IEventLoop& eventLoop) :
    modalPopupFactory{modalPopupFactory},
    eventLoop{eventLoop}
{
}

void CopyLogsPopup::Impl::processPopupInput(bool copyButtonClicked, bool closeButtonClicked, const CopyLogs& copyLogs)
{
    if (closeButtonClicked)
    {
        modalPopupFactory.close();
        return;
    }
    if(copyButtonClicked)
    {
        eventLoop.post([&](){

            //On eventloop

            LogScpWrapper::ProcessStartInfo process_start_info {
                .executable_path{"tr"},
                .arguments{"tr", "a-z", "A-Z"},
            };
            
            std::unique_ptr<LogScpWrapper::IPtyMaster> process{std::make_unique<LogScpWrapper::PtyMaster>(process_start_info)};

            process->start();

            auto& piped_child = process->getChild();

        });
        modalPopupFactory.close();
        return;
    }
}

CopyLogsPopup::CopyLogsPopup(IModalPopupFactory& modalPopupFactory, LogEventHandling::IEventLoop& eventLoop) :
    p{std::make_unique<Impl>(modalPopupFactory, eventLoop)}
{
}

CopyLogsPopup::~CopyLogsPopup() = default;

void CopyLogsPopup::drawCopyLogsPopup(ImVec2 popupPosition, ImVec2 popupSize)
{
    p->modalPopupFactory.open(popupPosition, popupSize, CopyLogsDefs::Name);
    p->modalPopupFactory.beginLayout(CopyLogsDefs::Name);

    std::vector<PopupButton> popupButtons{
        PopupButton{CopyLogsDefs::CopyBtn},
        PopupButton{CopyLogsDefs::CloseBtn}};
    p->modalPopupFactory.createButtonGroup(popupButtons);

    std::vector<PopupInputTextBox> popupSrcDestFolders{
        PopupInputTextBox{"Source Host Path", CopyLogsDefs::TextBoxWidth},
        PopupInputTextBox{"Destination Directory", CopyLogsDefs::TextBoxWidth}};
    p->modalPopupFactory.createInputTextBoxGroup(popupSrcDestFolders, "Directories", true);

    std::vector<PopupInputTextBox> jumpHosts{
        PopupInputTextBox{"Jump Host 1", CopyLogsDefs::TextBoxWidth},
        PopupInputTextBox{"Jump Host 2", CopyLogsDefs::TextBoxWidth},
        PopupInputTextBox{"Jump Host 3", CopyLogsDefs::TextBoxWidth}};
    p->modalPopupFactory.createInputTextBoxGroup(jumpHosts, "Jump Hosts", false, true);
    auto copyClicked = popupButtons[0].clicked;
    auto closeClicked = popupButtons[1].clicked;
    //TODO Implement input validation
    CopyLogs copyLogs;
    if(copyClicked)
    {
        copyLogs.srcHostPath = popupSrcDestFolders[0].input;
        copyLogs.dstDirectory = popupSrcDestFolders[1].input;
    }
    p->processPopupInput(copyClicked, closeClicked, copyLogs);

    p->modalPopupFactory.endLayout();
}

bool CopyLogsPopup::popupOpen()
{
    return p->modalPopupFactory.isPopupOpen();
}

}