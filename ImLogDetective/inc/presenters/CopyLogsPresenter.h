#pragma once
#include "ICopyLogsPresenter.h"
#include <memory>

namespace ImLogDetective {
    class IScpExecutor;
}

namespace ImLogDetective
{
class CopyLogsPopup;
class IMini;
class ProtectedInputPopup;

class CopyLogsPresenter : public ICopyLogsPresenter
{
public:
    CopyLogsPresenter(CopyLogsPopup& copyLogsPopup,
        ProtectedInputPopup& protectedInputPopup,
        ImLogDetective::IScpExecutor& scpExecutor,
        IMini& mini);
    ~CopyLogsPresenter();
    void update(bool openPopup, const ImVec2& popupPosition, const ImVec2& popupSize) final;
    void monitorCopyLogs() final;
    bool isClosed();
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}