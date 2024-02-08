#pragma once

#include <filesystem>
#include <utility>

struct ImVec2;

namespace LogAnalyzerTool
{

class ICopyLogsPopup
{
public:
    virtual ~ICopyLogsPopup() = default;
    virtual void drawCopyLogsPopup(ImVec2 popupPosition, ImVec2 popupSize) = 0;
    virtual bool popupOpen() = 0;

};

}