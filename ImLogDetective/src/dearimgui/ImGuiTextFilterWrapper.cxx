#include "dearimgui/ImGuiTextFilterWrapper.h"
#include "imgui.h"

namespace ImLogDetective
{

struct ImGuiTextFilterWrapper::Impl
{
    Impl(const std::string& label, float width);
    ~Impl() = default;

    const std::string label;
    float width;
    ImGuiTextFilter logLinesFilter;
};

ImGuiTextFilterWrapper::Impl::Impl(const std::string& label, float width) :
    label{label},
    width{width}
{
}

ImGuiTextFilterWrapper::ImGuiTextFilterWrapper(const std::string& label, float width) :
    p{std::make_unique<Impl>(label, width)}
{
}

ImGuiTextFilterWrapper::~ImGuiTextFilterWrapper() = default;

void ImGuiTextFilterWrapper::draw()
{
    p->logLinesFilter.Draw(p->label.c_str(), p->width);
}

bool ImGuiTextFilterWrapper::isActive() const
{
    return p->logLinesFilter.IsActive();
}

bool ImGuiTextFilterWrapper::passFilter(std::string_view text)
{
    return p->logLinesFilter.PassFilter(text.data());
}

}