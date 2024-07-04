
#ifndef IMLOGDETECTIVE_DEARIMGUI_IMGUITEXTFILTERWRAPPER_H
#define IMLOGDETECTIVE_DEARIMGUI_IMGUITEXTFILTERWRAPPER_H

#include <string>

namespace ImLogDetective
{

class ImGuiTextFilterWrapper
{
public:
    virtual ~ImGuiTextFilterWrapper() = default;
    virtual void draw() = 0;
    virtual bool isActive() const = 0;
    virtual bool passFilter(std::string_view text) = 0;
};

}

#endif