#pragma once

#include "dearimgui/IImGuiWidgetWrapper.h"
#include "gmock/gmock.h"
#include "ImVec.h"
#include <string>

namespace TestLogAnalyzerTool {

class ImGuiWidgetWrapperMock : public LogAnalyzerTool::IImGuiWidgetWrapper 
{
public:
    MOCK_METHOD(bool, beginPopupModal, (const std::string&));
    MOCK_METHOD(bool, button, (const std::string&));
    MOCK_METHOD(void, closeCurrentPopup, ());
    MOCK_METHOD(bool, collapsingHeader, (const std::string&));
    MOCK_METHOD(void, endPopup, ());
    MOCK_METHOD(bool, inputText, (const std::string&, char*));
    MOCK_METHOD(void, openPopup, (const std::string&));
    MOCK_METHOD(void, popItemWidth, ());
    MOCK_METHOD(void, pushItemWidth, (float));
    MOCK_METHOD(void, sameLine, ());
    MOCK_METHOD(void, setNextWindowPos, (const ImVec2&));
    MOCK_METHOD(void, setNextWindowSize, (const ImVec2&));
    MOCK_METHOD(void, textColored, (const ImVec4&, const std::string&));
    MOCK_METHOD(void, textUnformatted, (const std::string&));
};

}