#pragma once

#include "views/ISelectionMenuBar.h"
#include "gmock/gmock.h"

namespace TestImLogDetective {

class SelectionMenuBarMock : public ImLogDetective::ISelectionMenuBar 
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