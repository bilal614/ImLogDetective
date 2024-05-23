#pragma once

#include "dearimgui/ITabBar.h"
#include <memory>

namespace ImLogDetective
{

class TabBar : public ITabBar
{
public:
    TabBar(const std::string& tabBarName);
    ~TabBar();
    void drawTabBar(std::vector<std::reference_wrapper<TabBarItem>> tabItemsToDraw) override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}