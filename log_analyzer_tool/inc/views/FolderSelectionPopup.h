#pragma once

#include "views/IFolderSelectionPopup.h"
#include <memory>
#include <string>

namespace LogAnalyzerTool
{

class FolderSelectionPopup : public IFolderSelectionPopup
{
public:
    FolderSelectionPopup();
    ~FolderSelectionPopup();
    void drawFolderSelectionModalPopup(ImVec2 popupPosition, ImVec2 popupSize) override;
    std::string getSelectedFolder() override;
    bool popupOpen() override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;

};

}