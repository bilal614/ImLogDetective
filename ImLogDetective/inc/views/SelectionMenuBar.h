
#ifndef IMLOGDETECTIVE_VIEWS_SELECTIONMENUBAR_H
#define IMLOGDETECTIVE_VIEWS_SELECTIONMENUBAR_H

namespace ImLogDetective
{

class SelectionMenuBar
{
public:
    virtual ~SelectionMenuBar() = default;
    virtual void drawSelectionMenuBar() = 0;
    virtual bool selectFolderClicked() = 0;
    virtual void selectionFolderClosed() = 0;
    virtual float getInputScaleFactor() = 0;
    virtual bool copyRemoteLogsClicked() = 0;
    virtual void copyRemoteLogsClosed() = 0;

};

}

#endif