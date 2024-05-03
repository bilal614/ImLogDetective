#pragma once


struct ImVec2;

namespace LogAnalyzerTool
{

class ICopyLogsPresenter
{
public:
    virtual ~ICopyLogsPresenter() = default;
    virtual void update(bool openPopup, const ImVec2& popupPosition, const ImVec2& popupSize) = 0;
    virtual void monitorCopyLogs() = 0;
    virtual bool isClosed() = 0;
};

}