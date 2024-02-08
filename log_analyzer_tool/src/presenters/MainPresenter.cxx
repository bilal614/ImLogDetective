#include "presenters/MainPresenter.h"
#include "LogAnalyzerToolDefs.h"
#include "presenters/ILogFileTabsPresenter.h"
#include "presenters/IFileListPresenter.h"
#include "views/IFolderSelectionPopup.h"
#include "views/ICopyLogsPopup.h"
#include "dearimgui/IWindowFactory.h"
#include "dearimgui/IMainViewPort.h"
#include "dearimgui/IScopedImGuiWindow.h"
#include "imgui.h"

namespace LogAnalyzerTool
{

struct MainPresenter::Impl
{
    Impl(IWindowFactory& windowFactory,
        IMainViewPort& mainViewPort,
        ISelectionMenuBar& selectionMenuBar,
        IFolderSelectionPopup& folderSelectionPopup,
        ICopyLogsPopup& copyLogsPopup,
        ILogFileTabsPresenter& logFileTabsPresenter,
        IFileListPresenter& fileListPresenter);
    ~Impl() = default;

    void showFolderSelectionPopup();
    void showCopyRemoteLogsPopup();
    void showLogFilterSidebar(const ImVec2& mainWindowSize, 
        const ImVec2& mainWindowPos);
    void showMainBody(const ImVec2& mainWindowSize, 
        const ImVec2& mainWindowPos);

    IWindowFactory& windowFactory;
    IMainViewPort& mainViewPort;
    IFileListPresenter& fileListPresenter;
    ISelectionMenuBar& selectionMenuBar;
    IFolderSelectionPopup& folderSelectionPopup;
    ICopyLogsPopup& copyLogsPopup;
    ILogFileTabsPresenter& logFileTabsPresenter;
};

MainPresenter::Impl::Impl(IWindowFactory& windowFactory,
        IMainViewPort& mainViewPort,
        ISelectionMenuBar& selectionMenuBar,
        IFolderSelectionPopup& folderSelectionPopup,
        ICopyLogsPopup& copyLogsPopup,
        ILogFileTabsPresenter& logFileTabsPresenter,
        IFileListPresenter& fileListPresenter) :
    mainViewPort{mainViewPort},
    folderSelectionPopup{folderSelectionPopup},
    copyLogsPopup{copyLogsPopup},
    selectionMenuBar{selectionMenuBar},
    windowFactory{windowFactory},
    logFileTabsPresenter{logFileTabsPresenter},
    fileListPresenter{fileListPresenter}
{
}

void MainPresenter::Impl::showFolderSelectionPopup()
{
    auto popupSize = mainViewPort.getWorkAreaSize();
    popupSize.x *= Bounds::SmallPopupWindowRelativeToMain_X;
    popupSize.y *= Bounds::SmallPopupWindowRelativeToMain_Y;
    folderSelectionPopup.drawFolderSelectionModalPopup(mainViewPort.getViewportCenter(), popupSize);
    if(!folderSelectionPopup.popupOpen())
    {
        selectionMenuBar.selectionFolderClosed();
    }
}

void MainPresenter::Impl::showCopyRemoteLogsPopup()
{
    auto popupSize = mainViewPort.getWorkAreaSize();
    popupSize.x *= Bounds::LargePopupWindowRelativeToMain_X;
    popupSize.y *= Bounds::LargePopupWindowRelativeToMain_Y;
    copyLogsPopup.drawCopyLogsPopup(mainViewPort.getViewportCenter(), popupSize);
    if(!copyLogsPopup.popupOpen())
    {
        selectionMenuBar.copyRemoteLogsClosed();
    }
}

void MainPresenter::Impl::showLogFilterSidebar(const ImVec2& mainWindowSize, const ImVec2& mainWindowPos)
{
    ImVec2 fileListBoxPosition{mainWindowPos.x, mainWindowPos.y};
    ImVec2 fileListBoxSize{
        mainWindowSize.x*Bounds::SidebarRelativeToMainWinSize_X, 
        mainWindowSize.y*Bounds::MainContentRelativeToMainWinSize_Y};
    auto logFilterWindow = windowFactory.createChildWindow(WindowDefs::FileListWindow, fileListBoxPosition, fileListBoxSize);
    {
        if(auto folderSelection = folderSelectionPopup.getSelectedFolder(); folderSelection.first)
        {
            fileListPresenter.update(folderSelection.second);
        }
    }
}

void MainPresenter::Impl::showMainBody(const ImVec2& mainWindowSize, const ImVec2& mainWindowPos)
{
    ImVec2 mainContentBoxPosition{
        mainWindowPos.x*Bounds::MainBodyRelativeToMainWinPos_X,
        mainWindowPos.y};
    ImVec2 mainContentBoxSize{
        mainWindowSize.x*Bounds::MainBodyRelativeToMainWinSize_X, 
        mainWindowSize.y*Bounds::MainContentRelativeToMainWinSize_Y};
    auto mainContentChildWindow=windowFactory.createChildWindow(
        WindowDefs::LogsWindow,
        mainContentBoxPosition,
        mainContentBoxSize);
    logFileTabsPresenter.update(fileListPresenter.getSelectedFiles());
}

MainPresenter::MainPresenter(IWindowFactory& windowFactory,
        IMainViewPort& mainViewPort,
        ISelectionMenuBar& selectionMenuBar,
        IFolderSelectionPopup& folderSelectionPopup,
        ICopyLogsPopup& copyLogsPopup,
        ILogFileTabsPresenter& logFileTabsPresenter,
        IFileListPresenter& fileListPresenter) : 
    p {std::make_unique<Impl>(windowFactory,
        mainViewPort,
        selectionMenuBar,
        folderSelectionPopup,
        copyLogsPopup,
        logFileTabsPresenter,
        fileListPresenter)}
{
}

MainPresenter::~MainPresenter() = default;

void MainPresenter::update()
{
    // Create\Draw GUI widgets here in sequential order
    p->mainViewPort.setViewportScale(Bounds::ScaleFactorLowerBound + p->selectionMenuBar.getInputScaleFactor()/100.f);
    auto mainWindow = p->windowFactory.createWindow();
    p->selectionMenuBar.drawSelectionMenuBar();
    if(p->selectionMenuBar.selectFolderClicked())
    {
        p->showFolderSelectionPopup();
    }
    if(p->selectionMenuBar.copyRemoteLogsClicked())
    {
        p->showCopyRemoteLogsPopup();
    }

    auto mainWindowSize = mainWindow->getWindowSize();
    auto mainWindowPosition = mainWindow->getWindowPosition();

    p->showLogFilterSidebar(mainWindowSize, mainWindowPosition);
    mainWindow->onSameLine();
    p->showMainBody(mainWindowSize, mainWindowPosition);
}

}