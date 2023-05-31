#include "dearimgui/TabBar.h"
#include "imgui.h"

namespace LogAnalyzerTool
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

void TabBar::drawTabBar(const std::vector<TabBarItem>& tabItemsToDraw)
{
    if (ImGui::BeginTabBar(p->name.c_str(), p->tabBarFlags))
    {
        for(const auto& tabItem : tabItemsToDraw)
        {
            auto opened = tabItem.isOpen;
            if (opened && ImGui::BeginTabItem(tabItem.name.c_str(), &opened, p->tabItemFlags))
            {
                tabItem.draw();

                ImGui::EndTabItem();
            }
        }
        ImGui::EndTabBar();
    }
}

}