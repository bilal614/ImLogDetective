#pragma once

#include <memory>
#include "IMainView.h"
#include "views/ILogView.h"

namespace LogAnalyzerTool
{
class ILogView;
class ILogFilterView;
class IWindowFactory;
class MainViewModel;

class MainView : public IMainView
{
public:
    MainView(IWindowFactory& windowFactory, ILogFilterView& logFilterView, ILogView& logView, MainViewModel& mainViewModel);
    ~MainView();
    void show() override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};
}