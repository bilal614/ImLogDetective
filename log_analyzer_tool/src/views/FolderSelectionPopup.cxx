#include "views/FolderSelectionPopup.h"
#include <cstring>
#include <filesystem>

#include "imgui.h"


namespace {
    constexpr size_t MaxFolderPath{2048};

    std::string toString(const char* data)
    {
        return std::string(data, std::strlen(data));
    }
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
    bool folderSelectionDone;
};

FolderSelectionPopup::Impl::Impl() :
    folderPath{'\0'},
    popUpOpen{false},
    folderSelectionDone{false}
{
    folderPath.reserve(MaxFolderPath);
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
    p->folderSelectionDone = false;

    ImGui::SetNextWindowPos(popupPosition, ImGuiCond_Appearing, ImVec2(0.5f, 0.25f));
    ImGui::SetNextWindowSize(popupSize, ImGuiCond_FirstUseEver);

    if (ImGui::BeginPopupModal("Select Folder", NULL, ImGuiWindowFlags_NoDecoration))
    {
        ImGui::InputText("Select Folder", p->folderPath.data(), MaxFolderPath);
        if (ImGui::Button("OK"))
        {
            auto filePath = toString(p->folderPath.data());
            p->selectedFolderPath = filePath;
            p->popUpOpen = false;
            p->folderSelectionDone = true;
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("Close"))
        {
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

bool FolderSelectionPopup::currentFolderSelectionDone()
{
    bool currentFolderSelection = p->folderSelectionDone;
    p->folderSelectionDone = false;
    return currentFolderSelection;
}

}