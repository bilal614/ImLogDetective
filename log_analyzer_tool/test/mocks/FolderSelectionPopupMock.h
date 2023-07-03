#pragma once

#include "views/IFolderSelectionPopup.h"
#include "gmock/gmock.h"
#include "ImVec2.h"

namespace TestLogAnalyzerTool {

class FolderSelectionPopupMock : public LogAnalyzerTool::IFolderSelectionPopup 
{
public:
    MOCK_METHOD(void, drawFolderSelectionModalPopup, (ImVec2, ImVec2));
    MOCK_METHOD(std::string, getSelectedFolder,());
    MOCK_METHOD(bool, popupOpen, ());
    MOCK_METHOD(bool, currentFolderSelectionDone, ());
};

}