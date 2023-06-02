#pragma once

#include "dearimgui/IImGuiTextFilterWrapper.h"
#include "gmock/gmock.h"
#include <string>
#include <vector>

namespace TestLogAnalyzerTool {

class ImGuiTextFilterWrapperMock : public LogAnalyzerTool::IImGuiTextFilterWrapper 
{
public:
    MOCK_METHOD(void, draw, ());
    MOCK_METHOD(bool, isActive, (), (const));
    MOCK_METHOD(bool, passFilter, (std::string_view text));
};

}