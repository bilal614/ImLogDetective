
#ifndef IMLOGDETECTIVE_PRESENTERS_COPYLOGSPRESENTERIMPL_H
#define IMLOGDETECTIVE_PRESENTERS_COPYLOGSPRESENTERIMPL_H

#include "presenters/CopyLogsPresenter.h"
#include <memory>

namespace ImLogDetective {
    class IScpExecutor;
}

namespace ImLogDetective
{

class CopyLogsPopupImpl;
class Mini;
class ProtectedInputPopupImpl;

class CopyLogsPresenterImpl : public CopyLogsPresenter
{
public:
    CopyLogsPresenterImpl(CopyLogsPopupImpl& copyLogsPopup,
        ProtectedInputPopupImpl& protectedInputPopup,
        ImLogDetective::IScpExecutor& scpExecutor,
        Mini& mini);
    ~CopyLogsPresenterImpl();
    void update(bool openPopup, const ImVec2& popupPosition, const ImVec2& popupSize) final;
    void monitorCopyLogs() final;
    bool isClosed();
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}

#endif