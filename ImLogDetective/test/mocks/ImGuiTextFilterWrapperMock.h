#pragma once

#include "dearimgui/ImGuiTextFilterWrapper.h"
#include <gmock/gmock.h>
#include <string>
#include <vector>

namespace TestImLogDetective {

class ImGuiTextFilterWrapperMock : public ImLogDetective::ImGuiTextFilterWrapper 
{
public:
    MOCK_METHOD(void, draw, ());
    MOCK_METHOD(bool, isActive, (), (const));
    MOCK_METHOD(bool, passFilter, (std::string_view text));
};

}