#pragma once

#include "views/IModalPopupFactory.h"
#include "ImVec.h"
#include "gmock/gmock.h"

namespace TestImLogDetective {

class ModalPopupFactoryMock : public ImLogDetective::IModalPopupFactory 
{
public:
    MOCK_METHOD(void, open, (ImVec2, ImVec2, const std::string&));
    MOCK_METHOD(void, beginLayout, (const std::string&)); 
    MOCK_METHOD(bool, createButton, (ImLogDetective::PopupButton&));
    MOCK_METHOD(bool, createButtonGroup, (std::vector<ImLogDetective::PopupButton>&));
    MOCK_METHOD(bool, createInputTextBox, (const std::string&, std::string&, float));
    MOCK_METHOD(bool, createProtectedInputTextBox, (const std::string&, std::string&, float));
    MOCK_METHOD(bool, createInputTextBoxGroup, (
        std::vector<ImLogDetective::PopupInputTextBox>&, 
        const std::string&, 
        bool, 
        bool));
    MOCK_METHOD(bool, showErrorText, (const std::string&));
    MOCK_METHOD(void, endLayout, ());
    MOCK_METHOD(void, close, ());
    MOCK_METHOD(bool, isPopupOpen, ());
};

}