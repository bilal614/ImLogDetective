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
    ScopedImGuiMenuBar(std::initializer_list<std::pair<std::string, bool&>> menuItems, float& scaleFactor)
    {
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Menu"))
            {
                for(auto& menuItem : menuItems)
                {
                    if (ImGui::MenuItem(menuItem.first.c_str(), NULL, &menuItem.second))
                    {
                    }
                }

                ImGui::SliderFloat("Scale", &scaleFactor, 0.0f, 100.0f);
                ImGui::EndMenu();
            }
        }
    }

    ~ScopedImGuiMenuBar()
    {
        ImGui::EndMenuBar();
    }
};

}