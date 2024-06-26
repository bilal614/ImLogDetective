#include "dearimgui/ImGuiWidgetWrapper.h"
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

bool ImGuiWidgetWrapper::beginPopupModal(const std::string& name)
{
    return ImGui::BeginPopupModal(name.c_str(), NULL, ImGuiWindowFlags_NoDecoration);
}

bool ImGuiWidgetWrapper::button(const std::string& label)
{
    return ImGui::Button(label.c_str());
}

bool ImGuiWidgetWrapper::checkBox(std::string_view label, bool& checked)
{
    return ImGui::Checkbox(label.data(), &checked);
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
        boxLength < Common::MaxTextboxInputLength ? boxLength : Common::MaxTextboxInputLength);
}

bool ImGuiWidgetWrapper::inputPassword(const std::string& label, char* buf, size_t boxLength)
{
    return ImGui::InputText(label.c_str(), buf, 
        boxLength < Common::MaxTextboxInputLength ? boxLength : Common::MaxTextboxInputLength, 
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

void ImGuiWidgetWrapper::separator()
{
    ImGui::Separator();
}

void ImGuiWidgetWrapper::setNextWindowPos(const ImVec2& pos)
{
    ImGui::SetNextWindowPos(pos, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
}

void ImGuiWidgetWrapper::setNextWindowSize(const ImVec2& size)
{
    ImGui::SetNextWindowSize(size, ImGuiCond_Appearing);
}

void ImGuiWidgetWrapper::textColored(const ImVec4& color, std::string_view text)
{
    ImGui::TextColored(color, "%s", text.data());
}

void ImGuiWidgetWrapper::textUnformatted(std::string_view text)
{
    ImGui::TextUnformatted(text.data());
}

bool ImGuiWidgetWrapper::selectableText(const ImVec4& color, std::string_view text, bool selected)
{
    volatile auto textColorStyle = TextColorStyle(color);
    return text.empty() ? false : ImGui::Selectable(text.data(), selected);
}

}