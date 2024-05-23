#pragma once

#include "views/ISelectionMenuBar.h"
#include <memory>

namespace ImLogDetective
{

class SelectionMenuBar : public ISelectionMenuBar
{
public:
    SelectionMenuBar();
    ~SelectionMenuBar();
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