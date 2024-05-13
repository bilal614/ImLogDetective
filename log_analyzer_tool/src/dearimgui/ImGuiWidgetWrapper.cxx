#include "dearimgui/ImGuiWidgetWrapper.h"
#include "ImLogDetectiveDefs.h"
#include "imgui.h"

namespace ImLogDetective
{

bool ImGuiWidgetWrapper::beginPopupModal(const std::string& name)
{
    return ImGui::BeginPopupModal(name.c_str(), NULL, ImGuiWindowFlags_NoDecoration);
}

bool ImGuiWidgetWrapper::button(const std::string& label)
{
    return ImGui::Button(label.c_str());
}

void ImGuiWidgetWrapper::closeCurrentPopup()
{
    ImGui::CloseCurrentPopup();
}

bool ImGuiWidgetWrapper::collapsingHeader(const std::string& title)
{
    return ImGui::CollapsingHeader(title.c_str(), ImGuiTreeNodeFlags_None);
}

void ImGuiWidgetWrapper::endPopup()
{
    ImGui::EndPopup();
}

bool ImGuiWidgetWrapper::inputText(const std::string& label, char* buf, size_t boxLength)
{
    return ImGui::InputText(label.c_str(), buf, 
        boxLength < Bounds::MaxTextboxInputLength ? boxLength : Bounds::MaxTextboxInputLength);
}

bool ImGuiWidgetWrapper::inputPassword(const std::string& label, char* buf, size_t boxLength)
{
    return ImGui::InputText(label.c_str(), buf, 
        boxLength < Bounds::MaxTextboxInputLength ? boxLength : Bounds::MaxTextboxInputLength, 
        ImGuiInputTextFlags_Password);
}

void ImGuiWidgetWrapper::openPopup(const std::string& name)
{
    ImGui::OpenPopup(name.c_str());
}

void ImGuiWidgetWrapper::popItemWidth()
{
    ImGui::PopItemWidth();
}

void ImGuiWidgetWrapper::pushItemWidth(float width)
{
    ImGui::PushItemWidth(width);
}

void ImGuiWidgetWrapper::sameLine()
{
    ImGui::SameLine();
}

void ImGuiWidgetWrapper::setNextWindowPos(const ImVec2& pos)
{
    ImGui::SetNextWindowPos(pos, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
}

void ImGuiWidgetWrapper::setNextWindowSize(const ImVec2& size)
{
    ImGui::SetNextWindowSize(size, ImGuiCond_Appearing);
}

void ImGuiWidgetWrapper::textColored(const ImVec4& color, const std::string& text)
{
    ImGui::TextColored(color, "%s", text.data());
}

void ImGuiWidgetWrapper::textUnformatted(const std::string& text)
{
    ImGui::TextUnformatted(text.c_str());
}

}