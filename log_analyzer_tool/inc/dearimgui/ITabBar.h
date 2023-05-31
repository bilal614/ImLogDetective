#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

namespace LogAnalyzerTool
{

struct TabBarItem
{
    std::string name;
    bool isOpen;
    std::function<void()> draw;
};

class ITabBar
{
public:
    virtual ~ITabBar() = default;
    virtual void drawTabBar(const std::vector<TabBarItem>& tabItemsToDraw) = 0;
};

}