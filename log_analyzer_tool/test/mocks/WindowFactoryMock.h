#pragma once

#include "dearimgui/IWindowFactory.h"
#include "gmock/gmock.h"

namespace TestLogAnalyzerTool {

class WindowFactoryMock : public LogAnalyzerTool::IWindowFactory 
{
public:
    MOCK_METHOD(std::unique_ptr<LogAnalyzerTool::IScopedImGuiWindow>, createWindow, ());
    MOCK_METHOD(std::unique_ptr<LogAnalyzerTool::IScopedImGuiWindow>, createChildWindow, (const std::string& windowName));

};

}