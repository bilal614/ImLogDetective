
#ifndef IMLOGDETECTIVE_DEARIMGUI_TABBAR_H
#define IMLOGDETECTIVE_DEARIMGUI_TABBAR_H

#include <functional>
#include <string>
#include <tuple>
#include <vector>

namespace ImLogDetective
{

struct TabBarItem
{
    std::string name;
    bool isOpen;
    std::function<void()> draw;
};

class TabBar
{
public:
    virtual ~TabBar() = default;
    virtual void drawTabBar(std::vector<std::reference_wrapper<TabBarItem>> tabItemsToDraw) = 0;
};

}

#endif