#include "presenters/MainPresenter.h"
#include "views/ILogView.h"
#include "views/ILogFilterView.h"
#include "views/IFolderSelectionPopup.h"
#include "dearimgui/IWindowFactory.h"
#include "dearimgui/IMainViewPort.h"
#include "dearimgui/ScopedImGuiWindow.hpp"
#include "dearimgui/ITextWidgetFactory.h"

//TODO Remove later
#include "models/LogDataModel.h"
#include <string_view>

namespace LogAnalyzerTool
{

struct MainPresenter::Impl
{
    Impl(IWindowFactory& windowFactory,
        IMainViewPort& mainViewPort,
        IFolderSelectionMenuBar& folderSelectionMenuBar,
        IFolderSelectionPopup& folderSelectionPopup,
        ILogFilterView& logFilterView, 
        ILogView& logView);
    ~Impl() = default;

    IWindowFactory& windowFactory;
    IMainViewPort& mainViewPort;
    IFolderSelectionMenuBar& folderSelectionMenuBar;
    IFolderSelectionPopup& folderSelectionPopup;
    ILogFilterView& logFilterView;
    ILogView& logView;
    
    //TODO Remove later
    LogDataModel logDataModel;
};

MainPresenter::Impl::Impl(IWindowFactory& windowFactory,
        IMainViewPort& mainViewPort,
        IFolderSelectionMenuBar& folderSelectionMenuBar,
        IFolderSelectionPopup& folderSelectionPopup,
        ILogFilterView& logFilterView, 
        ILogView& logView) :
    mainViewPort{mainViewPort},
    folderSelectionPopup{folderSelectionPopup},
    folderSelectionMenuBar{folderSelectionMenuBar},
    logFilterView{logFilterView},
    logView{logView},
    windowFactory{windowFactory},
    logDataModel{"Dummy Data"}
{
}

MainPresenter::MainPresenter(IWindowFactory& windowFactory,
        IMainViewPort& mainViewPort,
        IFolderSelectionMenuBar& folderSelectionMenuBar,
        IFolderSelectionPopup& folderSelectionPopup,
        ILogFilterView& logFilterView, 
        ILogView& logView) : 
    p {std::make_unique<Impl>(windowFactory, mainViewPort, folderSelectionMenuBar, folderSelectionPopup, logFilterView, logView)}
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

    auto secondWindow = p->windowFactory.createChildWindow("Child Window");
    p->logFilterView.drawFilterCheckBoxes();

    auto dummyData = p->logDataModel.getLogData(); 
    for(auto data : dummyData)
    {
        if(data.find("DEBUG") != std::string_view::npos && p->logFilterView.getDebugChecked())
        {
            p->logView.drawLogLineText(data, TextColor::White);
        }
        if(data.find("INFO") != std::string_view::npos  && p->logFilterView.getInfoChecked())
        {
            p->logView.drawLogLineText(data, TextColor::White);
        }
        if(data.find("WARNING") != std::string_view::npos && p->logFilterView.getWarningChecked())
        {
            p->logView.drawLogLineText(data, TextColor::Orange);
        }
        if(data.find("ERROR") != std::string_view::npos && p->logFilterView.getErrorChecked())
        {
            p->logView.drawLogLineText(data, TextColor::Red);
        }
    }
}

}