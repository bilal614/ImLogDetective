
#ifndef IMLOGDETECTIVE_VIEWS_COPYLOGSPOPUPIMPL_H
#define IMLOGDETECTIVE_VIEWS_COPYLOGSPOPUPIMPL_H

#include "views/CopyLogsPopup.h"
#include <memory>
#include <string>


namespace ImLogDetective
{

class ModalPopupFactory;

class CopyLogsPopupImpl : public CopyLogsPopup
{
public:
    CopyLogsPopupImpl(ModalPopupFactory& modalPopup);
    ~CopyLogsPopupImpl();
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

#endif