
#ifndef IMLOGDETECTIVE_DEARIMGUI_SCOPEDIMGUIMENUBAR_H
#define IMLOGDETECTIVE_DEARIMGUI_SCOPEDIMGUIMENUBAR_H

#include "imgui.h"
#include "ImLogDetectiveDefs.h"
#include "dearimgui/ImGuiMenuBarWrapper.h"
#include <string>
#include <initializer_list>

namespace ImLogDetective
{

struct ScopedImGuiMenuBar
{
    ScopedImGuiMenuBar(
        ImGuiMenuBarWrapper& wrapper, 
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

    ImGuiMenuBarWrapper& menuBarWrapper;
};

}

#endif