#include "dearimgui/ModalPopup.h"
#include "imgui.h"

namespace LogAnalyzerTool
{

void ModalPopup::open(ImVec2 popupPosition, ImVec2 popupSize, const std::string& name)
{
    ImGui::OpenPopup(name.c_str());
    ImGui::SetNextWindowPos(popupPosition, ImGuiCond_Appearing, ImVec2(0.5f, 0.25f));
    ImGui::SetNextWindowSize(popupSize, ImGuiCond_FirstUseEver);
}

void ModalPopup::close()
{
    ImGui::CloseCurrentPopup();
}

}