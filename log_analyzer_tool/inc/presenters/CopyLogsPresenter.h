#pragma once
#include "ICopyLogsPresenter.h"
#include <memory>

namespace LogScpWrapper {
    class IScpExecutor;
}

namespace LogAnalyzerTool
{
class ICopyLogsPopup;
class IProtectedInputPopup;

class CopyLogsPresenter : public ICopyLogsPresenter
{
public:
    CopyLogsPresenter(ICopyLogsPopup& copyLogsPopup,
        IProtectedInputPopup& protectedInputPopup,
        LogScpWrapper::IScpExecutor& scpExecutor);
    ~CopyLogsPresenter();
    void update(bool openPopup, const ImVec2& popupPosition, const ImVec2& popupSize) final;
    void monitorCopyLogs() final;
    bool isClosed();
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}