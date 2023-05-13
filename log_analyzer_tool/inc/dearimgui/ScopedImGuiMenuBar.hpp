#pragma once

#include "imgui.h"
#include <functional>
#include <string>
#include <initializer_list>

//TODO
#include <iostream>

namespace LogAnalyzerTool
{

struct ScopedImGuiMenuBar
{
    ScopedImGuiMenuBar(std::initializer_list<std::pair<std::string, bool&>> menuItems) 
    {
        if (ImGui::BeginMenuBar())
        {
            for(auto& menuItem : menuItems)
            {
                if (ImGui::MenuItem(menuItem.first.c_str(), NULL, &menuItem.second))
                {
                }
            }
        }
    }

    ~ScopedImGuiMenuBar()
    {
        ImGui::EndMenuBar();
    }
};

}