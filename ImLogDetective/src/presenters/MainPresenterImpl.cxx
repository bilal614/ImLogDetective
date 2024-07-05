#include "presenters/MainPresenterImpl.h"
#include "ImLogDetectiveDefs.h"
#include "presenters/LogFileTabsPresenter.h"
#include "presenters/FileListPresenter.h"
#include "views/FolderSelectionPopup.h"
#include "models/Mini.h"
#include "presenters/CopyLogsPresenter.h"
#include "views/WindowFactory.h"
#include "dearimgui/MainViewPort.h"
#include "imgui.h"

#include <iostream>
#include <thread>

namespace ImLogDetective
{

struct MainPresenterImpl::Impl
{
    Impl(WindowFactory& windowFactory,
        MainViewPort& mainViewPort,
        SelectionMenuBar& selectionMenuBar,
        FolderSelectionPopup& folderSelectionPopup,
        LogFileTabsPresenter& logFileTabsPresenter,
        FileListPresenter& fileListPresenter,
        CopyLogsPresenter& copyLogsPresenter,
        Mini& mini);
    ~Impl() = default;

    void showFolderSelectionPopup();
    void showCopyRemoteLogsPopup(bool openPopup);
    void showLogFilterSidebar(const ImVec2& mainWindowSize, 
        const ImVec2& mainWindowPos);
    void showMainBody(const ImVec2& mainWindowSize, 
        const ImVec2& mainWindowPos);

    WindowFactory& windowFactory;
    MainViewPort& mainViewPort;
    FileListPresenter& fileListPresenter;
    SelectionMenuBar& selectionMenuBar;
    FolderSelectionPopup& folderSelectionPopup;
    LogFileTabsPresenter& logFileTabsPresenter;
    CopyLogsPresenter& copyLogsPresenter;
    Mini& mini;
};

MainPresenterImpl::Impl::Impl(WindowFactory& windowFactory,
        MainViewPort& mainViewPort,
        SelectionMenuBar& selectionMenuBar,
        FolderSelectionPopup& folderSelectionPopup,
        LogFileTabsPresenter& logFileTabsPresenter,
        FileListPresenter& fileListPresenter,
        CopyLogsPresenter& copyLogsPresenter,
        Mini& mini) :
    mainViewPort{mainViewPort},
    folderSelectionPopup{folderSelectionPopup},
    selectionMenuBar{selectionMenuBar},
    windowFactory{windowFactory},
    logFileTabsPresenter{logFileTabsPresenter},
    fileListPresenter{fileListPresenter},
    copyLogsPresenter{copyLogsPresenter},
    mini{mini}
{
    if(folderSelectionPopup.setInitialSelectedFolderPath(
        mini.get(IniDefs::SelectedFolderSection::Name, 
            IniDefs::SelectedFolderSection::LogDataFolder)))
    {
        std::cout << "Initial folder path not set" << std::endl;
    }
}

void MainPresenterImpl::Impl::showFolderSelectionPopup()
{
    auto popupSize = mainViewPort.getWorkAreaSize();
    popupSize.x *= LayoutBounds::SmallPopupWindowRelativeToMain_X;
    popupSize.y *= LayoutBounds::SmallPopupWindowRelativeToMain_Y;
    folderSelectionPopup.drawFolderSelectionModalPopup(mainViewPort.getViewportCenter(), popupSize);
    if(!folderSelectionPopup.popupOpen())
    {
        auto selectedFolder = folderSelectionPopup.getSelectedFolder();
        if(selectedFolder.first)
        {
            mini.set(IniDefs::SelectedFolderSection::Name, 
                IniDefs::SelectedFolderSection::LogDataFolder, 
                selectedFolder.second);
            mini.updateIniFile();
            fileListPresenter.update(selectedFolder.second, true);
        }
        selectionMenuBar.selectionFolderClosed();
    }
}

void MainPresenterImpl::Impl::showCopyRemoteLogsPopup(bool openPopup)
{
    auto popupSize = mainViewPort.getWorkAreaSize();
    popupSize.x *= LayoutBounds::LargePopupWindowRelativeToMain_X;
    popupSize.y *= LayoutBounds::LargePopupWindowRelativeToMain_Y;
    copyLogsPresenter.update(openPopup, mainViewPort.getViewportCenter(), popupSize);
    if(copyLogsPresenter.isClosed())
    {
        selectionMenuBar.copyRemoteLogsClosed();
    }
}

void MainPresenterImpl::Impl::showLogFilterSidebar(const ImVec2& mainWindowSize, const ImVec2& mainWindowPos)
{
    ImVec2 fileListBoxPosition{mainWindowPos.x, mainWindowPos.y};
    ImVec2 fileListBoxSize{
        mainWindowSize.x*LayoutBounds::SidebarRelativeToMainWinSize_X, 
        mainWindowSize.y*LayoutBounds::MainContentRelativeToMainWinSize_Y};
    auto logFilterWindow = windowFactory.createChildWindow(WindowDefs::FileListWindow, fileListBoxPosition, fileListBoxSize);
    {
        if(auto folderSelection = folderSelectionPopup.getSelectedFolder(); folderSelection.first)
        {
            fileListPresenter.update(folderSelection.second, false);
        }
    }
}

void MainPresenterImpl::Impl::showMainBody(const ImVec2& mainWindowSize, const ImVec2& mainWindowPos)
{
    ImVec2 mainContentBoxPosition{
        mainWindowPos.x*LayoutBounds::MainBodyRelativeToMainWinPos_X,
        mainWindowPos.y};
    ImVec2 mainContentBoxSize{
        mainWindowSize.x*LayoutBounds::MainBodyRelativeToMainWinSize_X, 
        mainWindowSize.y*LayoutBounds::MainContentRelativeToMainWinSize_Y};
    auto mainContentChildWindow=windowFactory.createChildWindow(
        WindowDefs::LogsWindow,
        mainContentBoxPosition,
        mainContentBoxSize);
    logFileTabsPresenter.update(fileListPresenter.getSelectedFiles());
}

MainPresenterImpl::MainPresenterImpl(WindowFactory& windowFactory,
        MainViewPort& mainViewPort,
        SelectionMenuBar& selectionMenuBar,
        FolderSelectionPopup& folderSelectionPopup,
        LogFileTabsPresenter& logFileTabsPresenter,
        FileListPresenter& fileListPresenter,
        CopyLogsPresenter& copyLogsPresenter,
        Mini& mini) : 
    p {std::make_unique<Impl>(windowFactory,
        mainViewPort,
        selectionMenuBar,
        folderSelectionPopup,
        logFileTabsPresenter,
        fileListPresenter,
        copyLogsPresenter,
        mini)}
{
}

MainPresenterImpl::~MainPresenterImpl() = default;

void MainPresenterImpl::update()
{
    // Create\Draw GUI widgets here in sequential order
    p->mainViewPort.setViewportScale(p->selectionMenuBar.getInputScaleFactor());
    auto mainWindow = p->windowFactory.createWindow();
    p->selectionMenuBar.drawSelectionMenuBar();
    if(p->selectionMenuBar.selectFolderClicked())
    {
        p->showFolderSelectionPopup();
    }

    p->showCopyRemoteLogsPopup(p->selectionMenuBar.copyRemoteLogsClicked());
    p->copyLogsPresenter.monitorCopyLogs();

    auto mainWindowSize = mainWindow->getWindowSize();
    auto mainWindowPosition = mainWindow->getWindowPosition();

    p->showLogFilterSidebar(mainWindowSize, mainWindowPosition);
    mainWindow->onSameLine();
    p->showMainBody(mainWindowSize, mainWindowPosition);
}

}