#include "MainView.h"
#include "MainViewModel.h"
#include "dearimgui/IWindowFactory.h"
#include "dearimgui/ScopedImGuiWindow.hpp"



namespace LogAnalyzerTool
{

struct MainView::Impl
{
    Impl(IWindowFactory& windowFactory, MainViewModel& viewModel);
    ~Impl() = default;

    IWindowFactory& windowFactory;
    MainViewModel& mainViewModel;
};

MainView::Impl::Impl(IWindowFactory& windowFactory,MainViewModel& viewModel) :
    mainViewModel{viewModel},
    windowFactory{windowFactory}
{
}

MainView::MainView(IWindowFactory& windowFactory, MainViewModel& viewModel) : 
    p {std::make_unique<Impl>(windowFactory, viewModel)}
{
}

MainView::~MainView() = default;

void MainView::show()
{
    // Create\Draw GUI widgets here in sequential order
    auto mainWindow = p->windowFactory.createWindow();
    //auto secondWindow = p->windowFactory.createChildWindow("Another Window");
}

}