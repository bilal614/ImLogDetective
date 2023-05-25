#pragma once

#include <string>

struct ImVec2;

namespace LogAnalyzerTool
{

class IFolderSelectionPopup
{
public:
    virtual ~IFolderSelectionPopup() = default;
    virtual void drawFolderSelectionModalPopup(ImVec2 popupPosition, ImVec2 popupSize) = 0;
    virtual std::string getSelectedFolder() = 0;
    virtual bool popupOpen() = 0;
    virtual bool currentFolderSelectionDone() = 0;

};

}