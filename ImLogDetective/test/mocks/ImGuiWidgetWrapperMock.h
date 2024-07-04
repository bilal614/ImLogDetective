#pragma once

#include "dearimgui/ImGuiWidgetWrapper.h"
#include "gmock/gmock.h"
#include "ImVec.h"
#include <string>

namespace TestImLogDetective {

class ImGuiWidgetWrapperMock : public ImLogDetective::ImGuiWidgetWrapper 
{
public:
    MOCK_METHOD(bool, beginPopupModal, (const std::string&));
    MOCK_METHOD(bool, button, (const std::string&));
    MOCK_METHOD(bool, checkBox,(std::string_view, bool&));
    MOCK_METHOD(void, closeCurrentPopup, ());
    MOCK_METHOD(bool, collapsingHeader, (const std::string&));
    MOCK_METHOD(void, endPopup, ());
    MOCK_METHOD(bool, inputText, (const std::string&, char*, size_t));
    MOCK_METHOD(bool, inputPassword,(const std::string&, char*, size_t));
    MOCK_METHOD(void, openPopup, (const std::string&));
    MOCK_METHOD(void, popItemWidth, ());
    MOCK_METHOD(void, pushItemWidth, (float));
    MOCK_METHOD(void, sameLine, ());
    MOCK_METHOD(void, separator, ());
    MOCK_METHOD(void, setNextWindowPos, (const ImVec2&));
    MOCK_METHOD(void, setNextWindowSize, (const ImVec2&));
    MOCK_METHOD(void, textColored, (const ImVec4&, std::string_view));
    MOCK_METHOD(void, textUnformatted, (std::string_view));
    MOCK_METHOD(bool, selectableText,(const ImVec4&, std::string_view, bool));
};

}