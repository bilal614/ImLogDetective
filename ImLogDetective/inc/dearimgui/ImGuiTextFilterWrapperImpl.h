
#ifndef IMLOGDETECTIVE_DEARIMGUI_IMGUITEXTFILTERWRAPPERIMPL_H
#define IMLOGDETECTIVE_DEARIMGUI_IMGUITEXTFILTERWRAPPERIMPL_H

#include "dearimgui/ImGuiTextFilterWrapper.h"
#include <memory>

namespace ImLogDetective
{

class ImGuiTextFilterWrapperImpl : public ImGuiTextFilterWrapper 
{
public:
    ImGuiTextFilterWrapperImpl(const std::string& label, float width);
    ~ImGuiTextFilterWrapperImpl();
    void draw() override;
    bool isActive() const override;
    bool passFilter(std::string_view text) override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}

#endif