#include "dearimgui/ImGuiTextFilterWrapperImpl.h"
#include "imgui.h"

namespace ImLogDetective
{

struct ImGuiTextFilterWrapperImpl::Impl
{
    Impl(const std::string& label, float width);
    ~Impl() = default;

    const std::string label;
    float width;
    ImGuiTextFilter logLinesFilter;
};

ImGuiTextFilterWrapperImpl::Impl::Impl(const std::string& label, float width) :
    label{label},
    width{width}
{
}

ImGuiTextFilterWrapperImpl::ImGuiTextFilterWrapperImpl(const std::string& label, float width) :
    p{std::make_unique<Impl>(label, width)}
{
}

ImGuiTextFilterWrapperImpl::~ImGuiTextFilterWrapperImpl() = default;

void ImGuiTextFilterWrapperImpl::draw()
{
    p->logLinesFilter.Draw(p->label.c_str(), p->width);
}

bool ImGuiTextFilterWrapperImpl::isActive() const
{
    return p->logLinesFilter.IsActive();
}

bool ImGuiTextFilterWrapperImpl::passFilter(std::string_view text)
{
    return p->logLinesFilter.PassFilter(text.data());
}

}