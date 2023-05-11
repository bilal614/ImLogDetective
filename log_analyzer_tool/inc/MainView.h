#pragma once

#include <memory>
#include "IMainView.h"
#include "dearimgui/ITextWidgetFactory.h"

namespace LogAnalyzerTool
{

class IWindowFactory;
class MainViewModel;

class MainView : public IMainView
{
public:
    MainView(IWindowFactory& windowFactory, ITextWidgetFactory& textWidgetFactory, MainViewModel& mainViewModel);
    ~MainView();
    void show() override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};
}