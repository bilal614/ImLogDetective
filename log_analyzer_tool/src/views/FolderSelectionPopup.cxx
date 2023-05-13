#include "views/FolderSelectionPopup.h"
#include <filesystem>

#include "imgui.h"


namespace {
    constexpr size_t MaxFolderPath{512};
}

namespace LogAnalyzerTool
{

struct FolderSelectionPopup::Impl
{
    Impl();
    ~Impl() = default;
    std::filesystem::path selectedFolderPath;
    std::string folderPath;
    bool popUpOpen;
};

FolderSelectionPopup::Impl::Impl() :
    folderPath{""},
    popUpOpen{false}
{
}

FolderSelectionPopup::FolderSelectionPopup() :
    p{std::make_unique<Impl>()}
{
}

FolderSelectionPopup::~FolderSelectionPopup() = default;

void FolderSelectionPopup::drawFolderSelectionModalPopup(ImVec2 popupPosition, ImVec2 popupSize)
{
    ImGui::OpenPopup("Select Folder");
    p->popUpOpen = true;

    ImGui::SetNextWindowPos(popupPosition, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSize(popupSize, ImGuiCond_FirstUseEver);

    if (ImGui::BeginPopupModal("Select Folder", NULL, ImGuiWindowFlags_NoDecoration))
    {
        ImGui::InputText("Select Folder", p->folderPath.data(), MaxFolderPath);
        if (ImGui::Button("Close"))
        {
            p->selectedFolderPath = p->folderPath;
            p->popUpOpen = false;
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

std::string FolderSelectionPopup::getSelectedFolder()
{
    //TODO validate selected folder path
    return p->selectedFolderPath.string();
}

bool FolderSelectionPopup::popupOpen()
{
    return p->popUpOpen;
}

}