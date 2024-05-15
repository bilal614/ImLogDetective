#pragma once

#include "views/IFolderSelectionPopup.h"
#include <memory>
#include <string>

namespace ImLogDetective
{

class IModalPopupFactory;

class FolderSelectionPopup : public IFolderSelectionPopup
{
public:
    FolderSelectionPopup(IModalPopupFactory& modalPopup);
    ~FolderSelectionPopup();
    bool setInitialSelectedFolderPath(const std::string& path) final;
    void drawFolderSelectionModalPopup(ImVec2 popupPosition, ImVec2 popupSize) final;
    std::pair<bool, std::filesystem::path> getSelectedFolder() final;
    bool popupOpen() final;
private:
    struct Impl;
    std::unique_ptr<Impl> p;

};

}