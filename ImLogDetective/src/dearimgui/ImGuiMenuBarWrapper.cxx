#include "dearimgui/ImGuiMenuBarWrapper.h"
#include "imgui.h"

namespace ImLogDetective
{

bool ImGuiMenuBarWrapper::beginMenuBar() const
{
    return ImGui::BeginMenuBar();
}

bool ImGuiMenuBarWrapper::beginMenu(std::string_view label) const
{
    return ImGui::BeginMenu(label.data());
}

void ImGuiMenuBarWrapper::endMenuBar() const
{
    ImGui::EndMenuBar();
}

void ImGuiMenuBarWrapper::endMenu() const
{
    ImGui::EndMenu();
}

bool ImGuiMenuBarWrapper::menuItem(std::string_view label, bool& selected)
{
    return ImGui::MenuItem(label.data(), NULL, &selected);
}

bool ImGuiMenuBarWrapper::slider(std::string_view label, int& val, int min, int max)
{
    return ImGui::SliderInt(label.data(), &val, min, max);
}

}