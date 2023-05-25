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

void TabBar::drawTabBar(const std::vector<std::tuple<std::string, bool, std::function<void()>>>& tabItemsToDraw)
{
    if (ImGui::BeginTabBar(p->name.c_str(), p->tabBarFlags))
    {
        for(const auto& tabItem : tabItemsToDraw)
        {
            auto tabName = std::get<0>(tabItem);
            auto opened = std::get<1>(tabItem);
            auto drawTabContents = std::get<2>(tabItem);
            if (opened && ImGui::BeginTabItem(tabName.c_str(), &opened, p->tabItemFlags))
            {
                drawTabContents();
                ImGui::EndTabItem();
            }
        }
        ImGui::EndTabBar();
    }
}

}