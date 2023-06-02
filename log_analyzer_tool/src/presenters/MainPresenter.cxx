#include "presenters/MainPresenter.h"
#include "presenters/ILogFileTabsPresenter.h"
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
        ILogFileTabsPresenter& logFileTabsPresenter);
    ~Impl() = default;

    IWindowFactory& windowFactory;
    IMainViewPort& mainViewPort;
    IFolderSelectionMenuBar& folderSelectionMenuBar;
    IFolderSelectionPopup& folderSelectionPopup;
    ILogFileTabsPresenter& logFileTabsPresenter;
};

MainPresenter::Impl::Impl(IWindowFactory& windowFactory,
        IMainViewPort& mainViewPort,
        IFolderSelectionMenuBar& folderSelectionMenuBar,
        IFolderSelectionPopup& folderSelectionPopup,
        ILogFileTabsPresenter& logFileTabsPresenter) :
    mainViewPort{mainViewPort},
    folderSelectionPopup{folderSelectionPopup},
    folderSelectionMenuBar{folderSelectionMenuBar},
    windowFactory{windowFactory},
    logFileTabsPresenter{logFileTabsPresenter}
{
}

MainPresenter::MainPresenter(IWindowFactory& windowFactory,
        IMainViewPort& mainViewPort,
        IFolderSelectionMenuBar& folderSelectionMenuBar,
        IFolderSelectionPopup& folderSelectionPopup,
        ILogFileTabsPresenter& logFileTabsPresenter) : 
    p {std::make_unique<Impl>(windowFactory, mainViewPort, folderSelectionMenuBar, folderSelectionPopup, logFileTabsPresenter)}
{
}

MainPresenter::~MainPresenter() = default;

void MainPresenter::update()
{
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

    //FileListViewPresenter

    //TODO provide vector of file paths to logFileTabsPresenter.update i.o. folder
    p->logFileTabsPresenter.update(p->folderSelectionPopup.getSelectedFolder());
}

}