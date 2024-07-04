
#ifndef IMLOGDETECTIVE_DEARIMGUI_TABBARIMPL_H
#define IMLOGDETECTIVE_DEARIMGUI_TABBARIMPL_H

#include "dearimgui/TabBar.h"
#include <memory>

namespace ImLogDetective
{

class TabBarImpl : public TabBar
{
public:
    TabBarImpl(const std::string& tabBarName);
    ~TabBarImpl();
    void drawTabBar(std::vector<std::reference_wrapper<TabBarItem>> tabItemsToDraw) override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}

#endif