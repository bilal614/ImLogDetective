#pragma once

#include <memory>
#include "dearimgui/IMainViewPort.h"
#include "presenters/IMainPresenter.h"
#include "views/IFolderSelectionMenuBar.h"
#include "views/ILogView.h"

namespace LogAnalyzerTool
{
class IFolderSelectionMenuBar;
class IFolderSelectionPopup;
class ILogView;
class ILogFilterView;
class IMainViewPort;
class IWindowFactory;

class MainPresenter : public IMainPresenter
{
public:
    MainPresenter(IWindowFactory& windowFactory,
        IMainViewPort& mainViewPort,
        IFolderSelectionMenuBar& folderSelectionMenuBar,
        IFolderSelectionPopup& folderSelectionPopup,
        ILogFilterView& logFilterView, 
        ILogView& logView);
    ~MainPresenter();
    void update() override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};
}