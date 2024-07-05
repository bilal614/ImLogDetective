
#ifndef IMLOGDETECTIVE_PRESENTERS_MAINPRESENTERIMPL_H
#define IMLOGDETECTIVE_PRESENTERS_MAINPRESENTERIMPL_H

#include <memory>
#include "dearimgui/MainViewPort.h"
#include "presenters/MainPresenter.h"
#include "views/SelectionMenuBar.h"
#include "views/LogView.h"

namespace ImLogDetective
{
class FileListPresenter;
class ISelectionMenuBar;
class CopyLogsPresenter;
class FolderSelectionPopup;
class LogFileTabsPresenter;
class MainViewPort;
class Mini;
class WindowFactory;

class MainPresenterImpl : public MainPresenter
{
public:
    MainPresenterImpl(WindowFactory& windowFactory,
        MainViewPort& mainViewPort,
        SelectionMenuBar& selectionMenuBar,
        FolderSelectionPopup& folderSelectionPopup,
        LogFileTabsPresenter& logFileTabsPresenter,
        FileListPresenter& fileListPresenter,
        CopyLogsPresenter& copyLogsPresenter,
        Mini& mini);
    ~MainPresenterImpl();
    void update() override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}

#endif