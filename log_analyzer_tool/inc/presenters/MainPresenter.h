#pragma once

#include <memory>
#include "dearimgui/IMainViewPort.h"
#include "presenters/ILogFilePresenter.h"
#include "presenters/IMainPresenter.h"
#include "views/ISelectionMenuBar.h"
#include "views/ILogView.h"

namespace LogAnalyzerTool
{
class IFileListPresenter;
class ISelectionMenuBar;
class ICopyLogsPopup;
class IFolderSelectionPopup;
class IMainViewPort;
class IWindowFactory;
class ILogFileTabsPresenter;

class MainPresenter : public IMainPresenter
{
public:
    MainPresenter(IWindowFactory& windowFactory,
        IMainViewPort& mainViewPort,
        ISelectionMenuBar& selectionMenuBar,
        IFolderSelectionPopup& folderSelectionPopup,
        ICopyLogsPopup& copyLogsPopup,
        ILogFileTabsPresenter& logFileTabsPresenter,
        IFileListPresenter& fileListPresenter);
    ~MainPresenter();
    void update() override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};
}