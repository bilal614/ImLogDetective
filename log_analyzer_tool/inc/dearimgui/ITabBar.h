#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

namespace LogAnalyzerTool
{

class ITabBar
{
public:
    virtual ~ITabBar() = default;
    virtual void drawTabBar(const std::vector<std::tuple<std::string, bool, std::function<void()>>>& tabItemsToDraw) = 0;
};

}