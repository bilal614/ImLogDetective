#pragma once

#include "views/IFolderSelectionPopup.h"
#include "gmock/gmock.h"
#include "ImVec.h"
#include <utility>

namespace TestLogAnalyzerTool {

using ValidFolderPath = std::pair<bool, std::filesystem::path>;

class FolderSelectionPopupMock : public LogAnalyzerTool::IFolderSelectionPopup 
{
public:
    MOCK_METHOD(void, drawFolderSelectionModalPopup, (ImVec2, ImVec2));
    MOCK_METHOD(ValidFolderPath, getSelectedFolder,());
    MOCK_METHOD(bool, popupOpen, ());
};

}