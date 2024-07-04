#include "dearimgui/ImGuiWidgetWrapperImpl.h"
#include "ImLogDetectiveDefs.h"
#include "imgui.h"

namespace {
    struct TextColorStyle
    {
        TextColorStyle(const ImVec4& color)
        {
            ImGui::PushStyleColor(ImGuiCol_Text, color);
        }

        ~TextColorStyle()
        {
            ImGui::PopStyleColor();
        }
    };
}

namespace ImLogDetective
{

bool ImGuiWidgetWrapperImpl::beginPopupModal(const std::string& name)
{
    return ImGui::BeginPopupModal(name.c_str(), NULL, ImGuiWindowFlags_NoDecoration);
}

bool ImGuiWidgetWrapperImpl::button(const std::string& label)
{
    return ImGui::Button(label.c_str());
}

bool ImGuiWidgetWrapperImpl::checkBox(std::string_view label, bool& checked)
{
    return ImGui::Checkbox(label.data(), &checked);
}

void ImGuiWidgetWrapperImpl::closeCurrentPopup()
{
    ImGui::CloseCurrentPopup();
}

bool ImGuiWidgetWrapperImpl::collapsingHeader(const std::string& title)
{
    return ImGui::CollapsingHeader(title.c_str(), ImGuiTreeNodeFlags_None);
}

void ImGuiWidgetWrapperImpl::endPopup()
{
    ImGui::EndPopup();
}

bool ImGuiWidgetWrapperImpl::inputText(const std::string& label, char* buf, size_t boxLength)
{
    return ImGui::InputText(label.c_str(), buf, 
        boxLength < Common::MaxTextboxInputLength ? boxLength : Common::MaxTextboxInputLength);
}

bool ImGuiWidgetWrapperImpl::inputPassword(const std::string& label, char* buf, size_t boxLength)
{
    return ImGui::InputText(label.c_str(), buf, 
        boxLength < Common::MaxTextboxInputLength ? boxLength : Common::MaxTextboxInputLength, 
        ImGuiInputTextFlags_Password);
}

void ImGuiWidgetWrapperImpl::openPopup(const std::string& name)
{
    ImGui::OpenPopup(name.c_str());
}

void ImGuiWidgetWrapperImpl::popItemWidth()
{
    ImGui::PopItemWidth();
}

void ImGuiWidgetWrapperImpl::pushItemWidth(float width)
{
    ImGui::PushItemWidth(width);
}

void ImGuiWidgetWrapperImpl::sameLine()
{
    ImGui::SameLine();
}

void ImGuiWidgetWrapperImpl::separator()
{
    ImGui::Separator();
}

void ImGuiWidgetWrapperImpl::setNextWindowPos(const ImVec2& pos)
{
    ImGui::SetNextWindowPos(pos, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
}

void ImGuiWidgetWrapperImpl::setNextWindowSize(const ImVec2& size)
{
    ImGui::SetNextWindowSize(size, ImGuiCond_Appearing);
}

void ImGuiWidgetWrapperImpl::textColored(const ImVec4& color, std::string_view text)
{
    ImGui::TextColored(color, "%s", text.data());
}

void ImGuiWidgetWrapperImpl::textUnformatted(std::string_view text)
{
    ImGui::TextUnformatted(text.data());
}

bool ImGuiWidgetWrapperImpl::selectableText(const ImVec4& color, std::string_view text, bool selected)
{
    volatile auto textColorStyle = TextColorStyle(color);
    return text.empty() ? false : ImGui::Selectable(text.data(), selected);
}

}