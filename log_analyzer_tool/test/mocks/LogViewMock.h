#pragma once

#include "views/ILogView.h"
#include "dearimgui/ITextWidgetFactory.h"
#include "gmock/gmock.h"

namespace TestLogAnalyzerTool {

class LogViewMock : public LogAnalyzerTool::ILogView 
{
public:
    MOCK_METHOD(void, drawLogLineText, (std::string_view logText, const LogAnalyzerTool::TextColor& color));
};

}