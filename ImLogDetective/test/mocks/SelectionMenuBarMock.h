
#ifndef IMLOGDETECTIVE_VIEWS_SELECTIONMENUBARMOCK_H
#define IMLOGDETECTIVE_VIEWS_SELECTIONMENUBARMOCK_H

#include "views/SelectionMenuBar.h"
#include "gmock/gmock.h"

namespace TestImLogDetective {

class SelectionMenuBarMock : public ImLogDetective::SelectionMenuBar 
{
public:
    MOCK_METHOD(void, drawSelectionMenuBar, ());
    MOCK_METHOD(bool, selectFolderClicked, ());
    MOCK_METHOD(void, selectionFolderClosed, ());
    MOCK_METHOD(float, getInputScaleFactor, ());
    MOCK_METHOD(bool, copyRemoteLogsClicked, ());
    MOCK_METHOD(void, copyRemoteLogsClosed, ());
};

}

#endif