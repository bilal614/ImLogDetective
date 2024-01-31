#include "presenters/MainPresenter.h"
#include "LogAnalyzerToolDefs.h"
#include "presenters/ILogFileTabsPresenter.h"
#include "presenters/IFileListPresenter.h"
#include "views/IFolderSelectionPopup.h"
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
        ILogFileTabsPresenter& logFileTabsPresenter,
        IFileListPresenter& fileListPresenter);
    ~Impl() = default;

    void showFolderSelectionPopup();
    void showLogFilterWindow(const ImVec2& mainWindowSize, 
        const ImVec2& mainWindowPos);
    void showMainContentWindow(const ImVec2& mainWindowSize, 
        const ImVec2& mainWindowPos);

    IWindowFactory& windowFactory;
    IMainViewPort& mainViewPort;
    IFileListPresenter& fileListPresenter;
    ISelectionMenuBar& selectionMenuBar;
    IFolderSelectionPopup& folderSelectionPopup;
    ILogFileTabsPresenter& logFileTabsPresenter;
};

MainPresenter::Impl::Impl(IWindowFactory& windowFactory,
        IMainViewPort& mainViewPort,
        ISelectionMenuBar& selectionMenuBar,
        IFolderSelectionPopup& folderSelectionPopup,
        ILogFileTabsPresenter& logFileTabsPresenter,
        IFileListPresenter& fileListPresenter) :
    mainViewPort{mainViewPort},
    folderSelectionPopup{folderSelectionPopup},
    selectionMenuBar{selectionMenuBar},
    windowFactory{windowFactory},
    logFileTabsPresenter{logFileTabsPresenter},
    fileListPresenter{fileListPresenter}
{
}

void MainPresenter::Impl::showFolderSelectionPopup()
{
    auto popupSize = mainViewPort.getWorkAreaSize();
    popupSize.x *= Bounds::PopupWindowRelativeToMain_X;
    popupSize.y *= Bounds::PopupWindowRelativeToMain_Y;
    folderSelectionPopup.drawFolderSelectionModalPopup(mainViewPort.getViewportCenter(), popupSize);
    if(!folderSelectionPopup.popupOpen())
    {
        selectionMenuBar.selectionFolderClosed();
    }
}

void MainPresenter::Impl::showLogFilterWindow(const ImVec2& mainWindowSize, const ImVec2& mainWindowPos)
{
    ImVec2 fileListBoxPosition{mainWindowPos.x*0.1f, 0.0};
    ImVec2 fileListBoxSize{mainWindowSize.x*0.1f, mainWindowSize.y*0.93f};
    auto logFilterWindow = windowFactory.createChildWindow(WindowDefs::FileListWindow, fileListBoxPosition, fileListBoxSize);
    {
        if(auto folderSelection = folderSelectionPopup.getSelectedFolder(); folderSelection.first)
        {
            fileListPresenter.update(folderSelection.second);
        }
    }
}

void MainPresenter::Impl::showMainContentWindow(const ImVec2& mainWindowSize, const ImVec2& mainWindowPos)
{
    ImVec2 mainContentBoxPosition{mainWindowPos.x*0.10f, mainWindowPos.y};
    ImVec2 mainContentBoxSize{mainWindowSize.x*0.89f, mainWindowSize.y*0.93f};
    auto mainContentChildWindow=windowFactory.createChildWindow(WindowDefs::LogsWindow, mainContentBoxPosition, mainContentBoxSize);
    logFileTabsPresenter.update(fileListPresenter.getSelectedFiles());
}

MainPresenter::MainPresenter(IWindowFactory& windowFactory,
        IMainViewPort& mainViewPort,
        ISelectionMenuBar& selectionMenuBar,
        IFolderSelectionPopup& folderSelectionPopup,
        ILogFileTabsPresenter& logFileTabsPresenter,
        IFileListPresenter& fileListPresenter) : 
    p {std::make_unique<Impl>(windowFactory,
        mainViewPort,
        selectionMenuBar,
        folderSelectionPopup,
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

    auto mainWindowSize = mainWindow->getWindowSize();
    auto mainWindowPosition = mainWindow->getWindowPosition();

    p->showLogFilterWindow(mainWindowSize, mainWindowPosition);
    mainWindow->onSameLine();
    p->showMainContentWindow(mainWindowSize, mainWindowPosition);
}

}