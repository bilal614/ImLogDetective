#pragma once

#include "presenters/ICopyLogsPresenter.h"
#include "gmock/gmock.h"
#include "ImVec.h"
#include <utility>

namespace TestLogAnalyzerTool {

class CopyLogsPresenterMock : public LogAnalyzerTool::ICopyLogsPresenter 
{
public:
    MOCK_METHOD(void, update, (bool, const ImVec2&, const ImVec2&));
    MOCK_METHOD(void, monitorCopyLogs, ());
    MOCK_METHOD(bool, isClosed, ());

};

}