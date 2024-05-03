#pragma once

#include "views/ICopyLogsPopup.h"
#include "gmock/gmock.h"
#include "ImVec.h"
#include <utility>

namespace TestLogAnalyzerTool {

using ValidFolderPath = std::pair<bool, std::filesystem::path>;

class CopyLogsPopupMock : public LogAnalyzerTool::ICopyLogsPopup 
{
public:
    MOCK_METHOD(void, drawCopyLogsPopup, (ImVec2, ImVec2));
    MOCK_METHOD(bool, isPopupOpen, ());
    MOCK_METHOD(void, closePopup, ());
    MOCK_METHOD(bool, copyBtnClicked, ()); 
    MOCK_METHOD(bool, closeBtnClicked, ());
    MOCK_METHOD(LogAnalyzerTool::CopyLogs, getInput, ()); 

};

}