#pragma once

#include <memory>
#include "IMainView.h"

namespace LogAnalyzerTool
{

class IWindowFactory;
class MainViewModel;

class MainView : public IMainView
{
public:
    MainView(IWindowFactory& windowFactory, MainViewModel& mainViewModel);
    ~MainView();
    void show() override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};
}