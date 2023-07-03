#pragma once

#include "dearimgui/IMainViewPort.h"
#include "gmock/gmock.h"
#include "ImVec2.h"

namespace TestLogAnalyzerTool {

class MainViewPortMock : public LogAnalyzerTool::IMainViewPort 
{
public:
    MOCK_METHOD(ImVec2, getAreaSize, (), (const));
    MOCK_METHOD(ImVec2, getWorkAreaSize, (), (const));
    MOCK_METHOD(ImVec2, getViewportPosition, (), (const));
    MOCK_METHOD(ImVec2, getViewportCenter, (), (const));
    MOCK_METHOD(void, setViewportScale, (const float));
};

}