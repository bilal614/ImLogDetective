#pragma once

#include "views/ICopyLogsPopup.h"
#include <memory>
#include <string>


namespace LogEventHandling {
    class IEventLoop;
}
namespace ImLogDetective
{

class IModalPopupFactory;
class IProtectedInputPopup;

class CopyLogsPopup : public ICopyLogsPopup
{
public:
    CopyLogsPopup(IModalPopupFactory& modalPopup, LogEventHandling::IEventLoop& eventLoop);
    ~CopyLogsPopup();
    void open(const ImVec2& popupPosition, const ImVec2& popupSize) final;
    void draw() final;
    void close() final;
    bool isOpen() final;
    bool okBtnClicked() final;
    bool closeBtnClicked() final;
    CopyLogs getInput() final;
    void initInput(const CopyLogs& input) final;
private:
    struct Impl;
    std::unique_ptr<Impl> p;

};

}