#pragma once

#include "dearimgui/ITabBar.h"

#include "gmock/gmock.h"
#include <vector>

namespace TestLogAnalyzerTool {

class TabBarMock : public LogAnalyzerTool::ITabBar 
{
public:
    MOCK_METHOD(void, drawTabBar, (const std::vector<LogAnalyzerTool::TabBarItem>&)); 
};

}