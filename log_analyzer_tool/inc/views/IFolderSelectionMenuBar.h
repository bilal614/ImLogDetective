#pragma once

namespace LogAnalyzerTool
{

class IFolderSelectionMenuBar
{
public:
    virtual ~IFolderSelectionMenuBar() = default;
    virtual void drawFolderSelectionMenuBar() = 0;
    virtual bool selectedFolderClicked() = 0;
    virtual void selectionFolderClosed() = 0;

};

}