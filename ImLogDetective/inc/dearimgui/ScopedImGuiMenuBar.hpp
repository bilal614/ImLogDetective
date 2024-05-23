#pragma once

#include "imgui.h"
#include "ImLogDetectiveDefs.h"
#include <functional>
#include <string>
#include <initializer_list>

namespace ImLogDetective
{

struct ScopedImGuiMenuBar
{
    ScopedImGuiMenuBar(std::initializer_list<std::pair<std::string, bool&>> menuItems, int& scaleFactor)
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

                ImGui::SliderInt("Scale", &scaleFactor, 
                    Scaling::MinScaleFactor, 
                    Scaling::MaxScaleFactor);
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