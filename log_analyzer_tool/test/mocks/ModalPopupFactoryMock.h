#pragma once

#include "dearimgui/IModalPopupFactory.h"
#include "ImVec2.h"
#include "gmock/gmock.h"

namespace TestLogAnalyzerTool {

class ModalPopupFactoryMock : public LogAnalyzerTool::IModalPopupFactory 
{
public:
    MOCK_METHOD(void, open, (ImVec2, ImVec2, const std::string&));
    MOCK_METHOD(void, beginLayout, (const std::string&)); 
    MOCK_METHOD(bool, createButtonGroup, (std::vector<LogAnalyzerTool::PopupButton>&));
    MOCK_METHOD(bool, createInputTextBox, (const std::string&, std::string&, float));
    MOCK_METHOD(bool, createInputTextBoxGroup, (
        std::vector<LogAnalyzerTool::PopupInputTextBox>&, 
        const std::string&, 
        bool, 
        bool));
    MOCK_METHOD(bool, showErrorText, (const std::string&));
    MOCK_METHOD(void, endLayout, ());
    MOCK_METHOD(void, close, ());
    MOCK_METHOD(bool, isPopupOpen, ());
};

}