#include "dearimgui/ImGuiMenuBarWrapperImpl.h"
#include "imgui.h"

namespace ImLogDetective
{

bool ImGuiMenuBarWrapperImpl::beginMenuBar() const
{
    return ImGui::BeginMenuBar();
}

bool ImGuiMenuBarWrapperImpl::beginMenu(std::string_view label) const
{
    return ImGui::BeginMenu(label.data());
}

void ImGuiMenuBarWrapperImpl::endMenuBar() const
{
    ImGui::EndMenuBar();
}

void ImGuiMenuBarWrapperImpl::endMenu() const
{
    ImGui::EndMenu();
}

bool ImGuiMenuBarWrapperImpl::menuItem(std::string_view label, bool& selected)
{
    return ImGui::MenuItem(label.data(), NULL, &selected);
}

bool ImGuiMenuBarWrapperImpl::slider(std::string_view label, int& val, int min, int max)
{
    return ImGui::SliderInt(label.data(), &val, min, max);
}

}