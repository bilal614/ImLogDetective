#include "MainView.h"
#include "MainViewModel.h"
#include "dearimgui/IWindowFactory.h"
#include "dearimgui/ScopedImGuiWindow.hpp"



namespace LogAnalyzerTool
{

struct MainView::Impl
{
    Impl(IWindowFactory& windowFactory, ITextWidgetFactory& textWidgetFactory, MainViewModel& viewModel);
    ~Impl() = default;

    IWindowFactory& windowFactory;
    ITextWidgetFactory& textWidgetFactory;
    MainViewModel& mainViewModel;
};

MainView::Impl::Impl(IWindowFactory& windowFactory, ITextWidgetFactory& textWidgetFactory, MainViewModel& viewModel) :
    mainViewModel{viewModel},
    textWidgetFactory{textWidgetFactory},
    windowFactory{windowFactory}
{
}

MainView::MainView(IWindowFactory& windowFactory, ITextWidgetFactory& textWidgetFactory, MainViewModel& viewModel) : 
    p {std::make_unique<Impl>(windowFactory, textWidgetFactory, viewModel)}
{
}

MainView::~MainView() = default;

void MainView::show()
{
    // Create\Draw GUI widgets here in sequential order
    auto mainWindow = p->windowFactory.createWindow();
    auto secondWindow = p->windowFactory.createChildWindow("Child Window");
    p->textWidgetFactory.createTextColored("Red", TextColor::Red);
    p->textWidgetFactory.createTextColored("Orange", TextColor::Orange);
    p->textWidgetFactory.createTextColored("Yellow", TextColor::Yellow);
    p->textWidgetFactory.createTextColored("Green", TextColor::Green);
    p->textWidgetFactory.createTextColored("White", TextColor::White);
}

}