#pragma once

#include <memory>
#include "dearimgui/IMainViewPort.h"
#include "presenters/ILogFilePresenter.h"
#include "presenters/IMainPresenter.h"
#include "views/ISelectionMenuBar.h"
#include "views/ILogView.h"

namespace ImLogDetective
{
class IFileListPresenter;
class ISelectionMenuBar;
class ICopyLogsPresenter;
class IFolderSelectionPopup;
class ILogFileTabsPresenter;
class IMainViewPort;
class IMini;
class IWindowFactory;

class MainPresenter : public IMainPresenter
{
public:
    MainPresenter(IWindowFactory& windowFactory,
        IMainViewPort& mainViewPort,
        ISelectionMenuBar& selectionMenuBar,
        IFolderSelectionPopup& folderSelectionPopup,
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