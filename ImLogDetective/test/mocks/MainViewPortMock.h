#pragma once

#include "dearimgui/MainViewPort.h"
#include "gmock/gmock.h"
#include "ImVec.h"

namespace TestImLogDetective {

class MainViewPortMock : public ImLogDetective::MainViewPort 
{
public:
    MOCK_METHOD(ImVec2, getAreaSize, (), (const));
    MOCK_METHOD(ImVec2, getWorkAreaSize, (), (const));
    MOCK_METHOD(ImVec2, getViewportPosition, (), (const));
    MOCK_METHOD(ImVec2, getViewportCenter, (), (const));
    MOCK_METHOD(void, setViewportScale, (const float));
};

}