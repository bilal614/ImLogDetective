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
    virtual void drawTabBar(std::vector<std::reference_wrapper<TabBarItem>> tabItemsToDraw) = 0;
};

}