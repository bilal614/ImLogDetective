#pragma once

#include <filesystem>
#include <utility>

struct ImVec2;

namespace ImLogDetective
{

class IFolderSelectionPopup
{
public:
    virtual ~IFolderSelectionPopup() = default;
    virtual bool setInitialSelectedFolderPath(const std::string& path) = 0;
    virtual void drawFolderSelectionModalPopup(ImVec2 popupPosition, ImVec2 popupSize) = 0;
    virtual std::pair<bool, std::filesystem::path> getSelectedFolder() = 0;
    virtual bool popupOpen() = 0;
};

}