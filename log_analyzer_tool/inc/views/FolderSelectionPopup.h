#pragma once

#include "views/IFolderSelectionPopup.h"
#include <memory>
#include <string>

namespace LogAnalyzerTool
{

class IModalPopupFactory;

class FolderSelectionPopup : public IFolderSelectionPopup
{
public:
    FolderSelectionPopup(IModalPopupFactory& modalPopup);
    ~FolderSelectionPopup();
    void drawFolderSelectionModalPopup(ImVec2 popupPosition, ImVec2 popupSize) override;
    std::pair<bool, std::filesystem::path> getSelectedFolder() override;
    bool popupOpen() override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;

};

}