#pragma once
#include "dearimgui/IImGuiMenuBarWrapper.h"
#include <gmock/gmock.h>
#include <string>

namespace TestImLogDetective
{

class ImGuiMenuBarWrapperMock : public ImLogDetective::IImGuiMenuBarWrapper
{
public:
    MOCK_METHOD(bool, beginMenuBar, (), (const));
    MOCK_METHOD(bool, beginMenu, (std::string_view), (const));
    MOCK_METHOD(void, endMenuBar, (), (const));
    MOCK_METHOD(void, endMenu, (), (const));
    MOCK_METHOD(bool, menuItem, (std::string_view, bool&));
    MOCK_METHOD(bool, slider, (std::string_view, int&, int, int));
};

}