#pragma once

#include "dearimgui/ITabBar.h"
#include <memory>

namespace LogAnalyzerTool
{

class TabBar : public ITabBar
{
public:
    TabBar(const std::string& tabBarName);
    ~TabBar();
    void drawTabBar(std::vector<TabBarItem>& tabItemsToDraw) override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}