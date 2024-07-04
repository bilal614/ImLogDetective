#pragma once

#include "dearimgui/TabBar.h"

#include "gmock/gmock.h"
#include <vector>

namespace TestImLogDetective {

class TabBarMock : public ImLogDetective::TabBar 
{
public:
    MOCK_METHOD(void, drawTabBar, (std::vector<std::reference_wrapper<ImLogDetective::TabBarItem>>)); 
};

}