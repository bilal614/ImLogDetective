#pragma once

#include "views/IFolderSelectionMenuBar.h"
#include <memory>

namespace LogAnalyzerTool
{

class FolderSelectionMenuBar : public IFolderSelectionMenuBar
{
public:
    FolderSelectionMenuBar();
    ~FolderSelectionMenuBar();
    void drawFolderSelectionMenuBar() override;
    bool selectedFolderClicked() override;
    void selectionFolderClosed() override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;

};

}