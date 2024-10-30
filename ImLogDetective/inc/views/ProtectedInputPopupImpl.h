
#ifndef IMLOGDETECTIVE_VIEWS_PROTECTEDINPUTPOPUPIMPL_H
#define IMLOGDETECTIVE_VIEWS_PROTECTEDINPUTPOPUPIMPL_H

#include "views/ProtectedInputPopup.h"
#include <memory>
#include <string>

struct ImVec2;

namespace ImLogDetective
{

class ModalPopupFactory;

class ProtectedInputPopupImpl : public Popup<std::string, NotCachedPopupInput>, ProtectedInputPopup
{
public:
    ProtectedInputPopupImpl(ModalPopupFactory& modalPopupFactory);
    ~ProtectedInputPopupImpl();
    void open(const ImVec2& popupPosition, const ImVec2& popupSize);
    void draw();
    void close();
    bool isOpen();
    bool okBtnClicked();
    bool closeBtnClicked();
    std::string getInput();
    void setPrompt(const std::string& prompt) final;
private:
    struct Impl;
    std::unique_ptr<Impl> p;

};

}

#endif