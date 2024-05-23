#include "dearimgui/TabBar.h"
#include "imgui.h"

namespace ImLogDetective
{

struct TabBar::Impl
{
    Impl(const std::string& tabBarName);
    ~Impl() = default;
    std::string name;
    ImGuiTabBarFlags tabBarFlags;
    ImGuiTabItemFlags tabItemFlags;

};

TabBar::Impl::Impl(const std::string& tabBarName) :
    name{tabBarName},
    tabBarFlags{ImGuiTabBarFlags_Reorderable},
    tabItemFlags{ImGuiTabItemFlags_None}
{
}

TabBar::TabBar(const std::string& tabBarName) :
    p{std::make_unique<Impl>(tabBarName)}
{

}

TabBar::~TabBar() = default;

void TabBar::drawTabBar(std::vector<std::reference_wrapper<TabBarItem>> tabItemsToDraw)
{
    if (ImGui::BeginTabBar(p->name.c_str(), p->tabBarFlags))
    {
        for(auto tabItem : tabItemsToDraw)
        {
            auto& item = tabItem.get();
            if (item.isOpen && ImGui::BeginTabItem(item.name.c_str(), &item.isOpen, p->tabItemFlags))
            {
                item.draw();

                ImGui::EndTabItem();
            }
        }
        ImGui::EndTabBar();
    }
}

}