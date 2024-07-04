#pragma once

#include <memory>
#include "dearimgui/MainViewPort.h"
#include "presenters/ILogFilePresenter.h"
#include "presenters/IMainPresenter.h"
#include "views/SelectionMenuBar.h"
#include "views/LogView.h"

namespace ImLogDetective
{
class IFileListPresenter;
class ISelectionMenuBar;
class ICopyLogsPresenter;
class FolderSelectionPopup;
class ILogFileTabsPresenter;
class MainViewPort;
class IMini;
class WindowFactory;

class MainPresenter : public IMainPresenter
{
public:
    MainPresenter(WindowFactory& windowFactory,
        MainViewPort& mainViewPort,
        SelectionMenuBar& selectionMenuBar,
        FolderSelectionPopup& folderSelectionPopup,
        ILogFileTabsPresenter& logFileTabsPresenter,
        IFileListPresenter& fileListPresenter,
        ICopyLogsPresenter& copyLogsPresenter,
        IMini& mini);
    ~MainPresenter();
    void update() override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};
}