#pragma once
#include "ICopyLogsPresenter.h"
#include <memory>

namespace ImLogDetective {
    class IScpExecutor;
}

namespace ImLogDetective
{
class CopyLogsPopup;
class Mini;
class ProtectedInputPopup;

class CopyLogsPresenter : public ICopyLogsPresenter
{
public:
    CopyLogsPresenter(CopyLogsPopup& copyLogsPopup,
        ProtectedInputPopup& protectedInputPopup,
        ImLogDetective::IScpExecutor& scpExecutor,
        Mini& mini);
    ~CopyLogsPresenter();
    void update(bool openPopup, const ImVec2& popupPosition, const ImVec2& popupSize) final;
    void monitorCopyLogs() final;
    bool isClosed();
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}