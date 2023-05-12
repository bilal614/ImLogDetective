#include "views/MainView.h"
#include "views/ILogView.h"
#include "views/ILogFilterView.h"
#include "MainViewModel.h"
#include "dearimgui/IWindowFactory.h"
#include "dearimgui/ScopedImGuiWindow.hpp"
#include "dearimgui/ITextWidgetFactory.h"

//TODO Remove later
#include "models/LogDataModel.h"
#include <string_view>

namespace LogAnalyzerTool
{

struct MainView::Impl
{
    Impl(IWindowFactory& windowFactory, ILogFilterView& logFilterView, ILogView& logView, MainViewModel& viewModel);
    ~Impl() = default;

    IWindowFactory& windowFactory;
    ILogFilterView& logFilterView;
    ILogView& logView;
    MainViewModel& mainViewModel;
    
    //TODO Remove later
    LogDataModel logDataModel;
};

MainView::Impl::Impl(IWindowFactory& windowFactory, ILogFilterView& logFilterView, ILogView& logView, MainViewModel& viewModel) :
    mainViewModel{viewModel},
    logFilterView{logFilterView},
    logView{logView},
    windowFactory{windowFactory},
    logDataModel{"Dummy Data"}
{
}

MainView::MainView(IWindowFactory& windowFactory, ILogFilterView& logFilterView, ILogView& logView, MainViewModel& viewModel) : 
    p {std::make_unique<Impl>(windowFactory, logFilterView, logView, viewModel)}
{
}

MainView::~MainView() = default;

void MainView::show()
{
    // Create\Draw GUI widgets here in sequential order
    auto mainWindow = p->windowFactory.createWindow();
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