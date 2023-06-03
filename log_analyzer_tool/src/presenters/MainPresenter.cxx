#include "presenters/MainPresenter.h"
#include "LogAnalyzerToolDefs.h"
#include "presenters/ILogFileTabsPresenter.h"
#include "presenters/IFileListPresenter.h"
#include "views/IFolderSelectionPopup.h"
#include "dearimgui/IWindowFactory.h"
#include "dearimgui/IMainViewPort.h"
#include "dearimgui/IScopedImGuiWindow.h"
#include "imgui.h" // Unfortunately needed because of ImVec2

namespace LogAnalyzerTool
{

struct MainPresenter::Impl
{
    Impl(IWindowFactory& windowFactory,
        IMainViewPort& mainViewPort,
        IFolderSelectionMenuBar& folderSelectionMenuBar,
        IFolderSelectionPopup& folderSelectionPopup,
        ILogFileTabsPresenter& logFileTabsPresenter,
        IFileListPresenter& fileListPresenter);
    ~Impl() = default;

    IWindowFactory& windowFactory;
    IMainViewPort& mainViewPort;
    IFileListPresenter& fileListPresenter;
    IFolderSelectionMenuBar& folderSelectionMenuBar;
    IFolderSelectionPopup& folderSelectionPopup;
    ILogFileTabsPresenter& logFileTabsPresenter;
};

MainPresenter::Impl::Impl(IWindowFactory& windowFactory,
        IMainViewPort& mainViewPort,
        IFolderSelectionMenuBar& folderSelectionMenuBar,
        IFolderSelectionPopup& folderSelectionPopup,
        ILogFileTabsPresenter& logFileTabsPresenter,
        IFileListPresenter& fileListPresenter) :
    mainViewPort{mainViewPort},
    folderSelectionPopup{folderSelectionPopup},
    folderSelectionMenuBar{folderSelectionMenuBar},
    windowFactory{windowFactory},
    logFileTabsPresenter{logFileTabsPresenter},
    fileListPresenter{fileListPresenter}
{
}

MainPresenter::MainPresenter(IWindowFactory& windowFactory,
        IMainViewPort& mainViewPort,
        IFolderSelectionMenuBar& folderSelectionMenuBar,
        IFolderSelectionPopup& folderSelectionPopup,
        ILogFileTabsPresenter& logFileTabsPresenter,
        IFileListPresenter& fileListPresenter) : 
    p {std::make_unique<Impl>(windowFactory,
        mainViewPort,
        folderSelectionMenuBar,
        folderSelectionPopup,
        logFileTabsPresenter,
        fileListPresenter)}
{
}

MainPresenter::~MainPresenter() = default;

void MainPresenter::update()
{
    //TODO Move Layout logic elsewhere
    // Create\Draw GUI widgets here in sequential order
    auto mainWindow = p->windowFactory.createWindow();
    p->folderSelectionMenuBar.drawFolderSelectionMenuBar();
    if(p->folderSelectionMenuBar.selectedFolderClicked())
    {
        auto popupSize = p->mainViewPort.getWorkAreaSize();
        popupSize.x = popupSize.x*0.25;
        popupSize.y = popupSize.y*0.25;
        p->folderSelectionPopup.drawFolderSelectionModalPopup(p->mainViewPort.getViewportCenter(), popupSize);
        if(!p->folderSelectionPopup.popupOpen())
        {
            p->folderSelectionMenuBar.selectionFolderClosed();
        }
    }

    auto mainWindowSize = mainWindow->getWindowSize();
    auto mainWindowPosition = mainWindow->getWindowPosition();

    {
        //FileListViewPresenter
        ImVec2 fileListBoxPosition{mainWindowPosition.x*0.1f, 0.0};
        ImVec2 fileListBoxSize{mainWindowSize.x*0.1f, 0.0};
        //TODO provide vector of file paths to logFileTabsPresenter.update i.o. folder
        auto logFilterWindow = p->windowFactory.createChildWindow(FileListWindow, fileListBoxPosition, fileListBoxSize);
        {
            p->fileListPresenter.update(p->folderSelectionPopup.getSelectedFolder());
        }
    }
    ImGui::SameLine();
    {
        ImVec2 mainContentBoxPosition{mainWindowPosition.x*0.10f, mainWindowPosition.y};
        ImVec2 mainContentBoxSize{mainWindowSize.x*0.89f, 0.0};
        auto mainContentChildWindow=p->windowFactory.createChildWindow(LogsWindow, mainContentBoxPosition, mainContentBoxSize);
        p->logFileTabsPresenter.update(p->folderSelectionPopup.getSelectedFolder());
    }
}

}