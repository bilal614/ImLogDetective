
#ifndef IMLOGDETECTIVE_VIEWS_COPYLOGSPOPUPIMPL_H
#define IMLOGDETECTIVE_VIEWS_COPYLOGSPOPUPIMPL_H

#include "views/Popup.h"
#include "views/CopyLogs.h"
#include <memory>
#include <string>


namespace ImLogDetective
{

class ModalPopupFactory;

class CopyLogsPopupImpl : public Popup<CopyLogs, CachedCopyLogsPopupInput>
{
public:
    CopyLogsPopupImpl(ModalPopupFactory& modalPopup);
    ~CopyLogsPopupImpl();
    void open(const ImVec2& popupPosition, const ImVec2& popupSize);
    void draw();
    void close();
    bool isOpen();
    bool okBtnClicked();
    bool closeBtnClicked();
    CopyLogs getInput();
private:
    void resetInternalState();
    bool validateInput();

private:
    ModalPopupFactory& modalPopupFactory;
    bool copyClicked;
    bool closeClicked;
    bool opened;
};

}

#endif