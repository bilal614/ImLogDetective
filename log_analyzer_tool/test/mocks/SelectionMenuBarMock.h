#pragma once

#include "views/ISelectionMenuBar.h"
#include "gmock/gmock.h"

namespace TestLogAnalyzerTool {

class SelectionMenuBarMock : public LogAnalyzerTool::ISelectionMenuBar 
{
public:
    MOCK_METHOD(void, drawSelectionMenuBar, ());
    MOCK_METHOD(bool, selectFolderClicked, ());
    MOCK_METHOD(void, selectionFolderClosed, ());
    MOCK_METHOD(float, getInputScaleFactor, ());
};

}