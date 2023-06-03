#pragma once

#include "dearimgui/IScopedImGuiWindow.h"
#include "gmock/gmock.h"

#include "imgui.h" //Unfortunately needed

namespace TestLogAnalyzerTool {

class ScopedImGuiWindowMock : public LogAnalyzerTool::IScopedImGuiWindow 
{
public:
    MOCK_METHOD(LogAnalyzerTool::WindowType, getWindowType, ());
    MOCK_METHOD(ImVec2, getWindowPosition, ());
    MOCK_METHOD(ImVec2, getWindowSize,());
};

}