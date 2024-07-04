
#ifndef IMLOGDETECTIVE_DEARIMGUI_IMGUIMENUBARWRAPPER_H
#define IMLOGDETECTIVE_DEARIMGUI_IMGUIMENUBARWRAPPER_H

#include <string>

namespace ImLogDetective
{

class ImGuiMenuBarWrapper
{
public:
    virtual ~ImGuiMenuBarWrapper() = default;
    virtual bool beginMenuBar() const = 0;
    virtual bool beginMenu(std::string_view label) const = 0;
    virtual void endMenuBar() const = 0;
    virtual void endMenu() const = 0;
    virtual bool menuItem(std::string_view label, bool& selected) = 0;
    virtual bool slider(std::string_view label, int& val, int min, int max) = 0;
};

}

#endif