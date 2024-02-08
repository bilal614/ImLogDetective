#pragma once

namespace LogAnalyzerTool
{

class ISelectionMenuBar
{
public:
    virtual ~ISelectionMenuBar() = default;
    virtual void drawSelectionMenuBar() = 0;
    virtual bool selectFolderClicked() = 0;
    virtual void selectionFolderClosed() = 0;
    virtual float getInputScaleFactor() = 0;
    virtual bool copyRemoteLogsClicked() = 0;
    virtual void copyRemoteLogsClosed() = 0;

};

}