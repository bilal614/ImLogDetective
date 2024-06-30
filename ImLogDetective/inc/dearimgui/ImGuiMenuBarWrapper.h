#pragma once
#include "dearimgui/IImGuiMenuBarWrapper.h"

namespace ImLogDetective
{

class ImGuiMenuBarWrapper : public IImGuiMenuBarWrapper
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