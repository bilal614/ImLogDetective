
#ifndef IMLOGDETECTIVE_DEARIMGUI_IMGUIMENUBARWRAPPERIMPL_H
#define IMLOGDETECTIVE_DEARIMGUI_IMGUIMENUBARWRAPPERIMPL_H

#include "dearimgui/ImGuiMenuBarWrapper.h"

namespace ImLogDetective
{

class ImGuiMenuBarWrapperImpl : public ImGuiMenuBarWrapper
{
public:
    bool beginMenuBar() const final;
    bool beginMenu(std::string_view label) const final;
    void endMenuBar() const final;
    void endMenu() const final;
    bool menuItem(std::string_view label, bool& selected) final;
    bool slider(std::string_view label, int& val, int min, int max) final;
};

}

#endif