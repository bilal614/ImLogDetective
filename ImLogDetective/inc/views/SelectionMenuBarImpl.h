
#ifndef IMLOGDETECTIVE_VIEWS_SELECTIONMENUBARIMPL_H
#define IMLOGDETECTIVE_VIEWS_SELECTIONMENUBARIMPL_H

#include "views/SelectionMenuBar.h"
#include <memory>

namespace ImLogDetective
{

class IImGuiMenuBarWrapper;

class SelectionMenuBarImpl : public SelectionMenuBar
{
public:
    SelectionMenuBarImpl(IImGuiMenuBarWrapper& wrapper);
    ~SelectionMenuBarImpl();
    void drawSelectionMenuBar() override;
    bool selectFolderClicked() override;
    void selectionFolderClosed() override;
    float getInputScaleFactor() override;
    bool copyRemoteLogsClicked() override;
    void copyRemoteLogsClosed() override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;

};

}

#endif