#pragma once

#include "views/ICopyLogsPopup.h"
#include <memory>
#include <string>

namespace LogAnalyzerTool
{

class IModalPopupFactory;

class CopyLogsPopup : public ICopyLogsPopup
{
public:
    CopyLogsPopup(IModalPopupFactory& modalPopup);
    ~CopyLogsPopup();
    void drawCopyLogsPopup(ImVec2 popupPosition, ImVec2 popupSize) override;
    bool popupOpen() override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;

};

}