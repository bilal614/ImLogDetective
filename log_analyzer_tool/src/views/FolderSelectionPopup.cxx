#include "views/FolderSelectionPopup.h"
#include "dearimgui/IModalPopup.h"
#include "LogAnalyzerToolDefs.h"
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
    Impl(IModalPopup& modalPopup);
    ~Impl() = default;
    bool validateSelectedFolder(const std::filesystem::path& path);
    void processPopupInput(
        bool closeButtonClicked, 
        bool okButtonClicked);
    void closePopup();

    std::filesystem::path selectedFolderPath;
    std::string folderPath;
    bool popUpOpen;
    bool invalidFolderSelected;
    IModalPopup& modalPopup;
};

FolderSelectionPopup::Impl::Impl(IModalPopup& modalPopup) :
    folderPath(MaxFolderPath, '\0'),
    popUpOpen{false},
    invalidFolderSelected{false},
    modalPopup{modalPopup}
{
}

bool FolderSelectionPopup::Impl::validateSelectedFolder(const std::filesystem::path& path)
{
    return std::filesystem::is_directory(path);
}

void FolderSelectionPopup::Impl::closePopup()
{
    popUpOpen = false;
    invalidFolderSelected = false;
    modalPopup.close();
}

void FolderSelectionPopup::Impl::processPopupInput(bool closeButtonClicked, bool okButtonClicked)
{
    if (closeButtonClicked)
    {
        closePopup();
        return;
    }

    if(okButtonClicked)
    { 
        selectedFolderPath = std::filesystem::path{folderPath};
        if(invalidFolderSelected = !validateSelectedFolder(std::filesystem::path{folderPath}); !invalidFolderSelected)
        {
            selectedFolderPath = std::filesystem::path{toString(folderPath.data())};
            closePopup();
            return;
        }
    }
    if(invalidFolderSelected)
    {
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "%s", ErrorMessage::InvalidDirectory);
    }
}

FolderSelectionPopup::FolderSelectionPopup(IModalPopup& modalPopup) :
    p{std::make_unique<Impl>(modalPopup)}
{
}

FolderSelectionPopup::~FolderSelectionPopup() = default;

void FolderSelectionPopup::drawFolderSelectionModalPopup(ImVec2 popupPosition, ImVec2 popupSize)
{
    p->modalPopup.open(popupPosition, popupSize, SelectFolderPopup::Name);
    p->popUpOpen = true;

    if (ImGui::BeginPopupModal(SelectFolderPopup::Name, NULL, ImGuiWindowFlags_NoDecoration))
    {
        ImGui::InputText(SelectFolderPopup::Name, p->folderPath.data(), MaxFolderPath);
        auto okButtonClicked = ImGui::Button("OK");
        ImGui::SameLine();
        auto closeButtonClicked = ImGui::Button("Close");
        p->processPopupInput(closeButtonClicked, okButtonClicked);
        ImGui::EndPopup();
    }
}

std::pair<bool, std::filesystem::path> FolderSelectionPopup::getSelectedFolder()
{
    return {p->validateSelectedFolder(p->selectedFolderPath), p->selectedFolderPath};
}

bool FolderSelectionPopup::popupOpen()
{
    return p->popUpOpen;
}

}