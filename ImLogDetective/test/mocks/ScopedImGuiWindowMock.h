#pragma once

#include "dearimgui/ScopedImGuiWindow.h"
#include "gmock/gmock.h"
#include "ImVec.h"

namespace TestImLogDetective {

class ScopedImGuiWindowMock : public ImLogDetective::ScopedImGuiWindow 
{
public:
    MOCK_METHOD(ImLogDetective::WindowType, getWindowType, ());
    MOCK_METHOD(ImVec2, getWindowPosition, ());
    MOCK_METHOD(ImVec2, getWindowSize,());
    MOCK_METHOD(void, onSameLine, ());
};

}