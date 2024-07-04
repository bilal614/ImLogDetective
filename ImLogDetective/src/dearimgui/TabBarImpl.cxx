#include "dearimgui/TabBarImpl.h"
#include "imgui.h"

namespace ImLogDetective
{

struct TabBarImpl::Impl
{
    Impl(const std::string& tabBarName);
    ~Impl() = default;
    std::string name;
    ImGuiTabBarFlags tabBarFlags;
    ImGuiTabItemFlags tabItemFlags;

};

TabBarImpl::Impl::Impl(const std::string& tabBarName) :
    name{tabBarName},
    tabBarFlags{ImGuiTabBarFlags_Reorderable},
    tabItemFlags{ImGuiTabItemFlags_None}
{
}

TabBarImpl::TabBarImpl(const std::string& tabBarName) :
    p{std::make_unique<Impl>(tabBarName)}
{

}

TabBarImpl::~TabBarImpl() = default;

void TabBarImpl::drawTabBar(std::vector<std::reference_wrapper<TabBarItem>> tabItemsToDraw)
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