#pragma once

#include "dearimgui/ITabBar.h"

#include "gmock/gmock.h"
#include <vector>

namespace TestImLogDetective {

class TabBarMock : public ImLogDetective::ITabBar 
{
public:
    MOCK_METHOD(void, drawTabBar, (std::vector<std::reference_wrapper<ImLogDetective::TabBarItem>>)); 
};

}