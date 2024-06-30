#pragma once

#include "imgui.h"
#include "ImLogDetectiveDefs.h"
#include "dearimgui/IImGuiMenuBarWrapper.h"
#include <string>
#include <initializer_list>

namespace ImLogDetective
{

struct ScopedImGuiMenuBar
{
    ScopedImGuiMenuBar(
        IImGuiMenuBarWrapper& wrapper, 
        std::initializer_list<std::pair<std::string, bool&>> menuItems, 
        int& scaleFactor) :
        menuBarWrapper{wrapper}
    {
        if(menuBarWrapper.beginMenuBar())
        {
            if(menuBarWrapper.beginMenu(MenuBar::Name))
            {
                for(auto& menuItem : menuItems)
                {
                    if (menuBarWrapper.menuItem(menuItem.first, menuItem.second))
                    {
                    }
                }
                menuBarWrapper.slider(MenuBar::ScaleLabel, scaleFactor, Scaling::MinScaleFactor, Scaling::MaxScaleFactor);
                menuBarWrapper.endMenu();
            }
        }
    }

    ~ScopedImGuiMenuBar()
    {
        menuBarWrapper.endMenuBar();
    }

    IImGuiMenuBarWrapper& menuBarWrapper;
};

}