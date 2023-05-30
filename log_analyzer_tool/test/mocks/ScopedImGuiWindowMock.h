#pragma once

#include "dearimgui/IScopedImGuiWindow.h"
#include "gmock/gmock.h"

namespace TestLogAnalyzerTool {

class ScopedImGuiWindowMock : public LogAnalyzerTool::IScopedImGuiWindow 
{
public:
    MOCK_METHOD(LogAnalyzerTool::WindowType, getWindowType, ());
};

}