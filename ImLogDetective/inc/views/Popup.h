
#ifndef IMLOGDETECTIVE_VIEWS_POPUP_H
#define IMLOGDETECTIVE_VIEWS_POPUP_H

#include <string>

struct ImVec2;

namespace ImLogDetective
{

template <class T>
class Popup
{
public:
    virtual ~Popup() = default;
    virtual void open(const ImVec2& popupPosition, const ImVec2& popupSize) = 0;
    virtual void draw() = 0;
    virtual void close() = 0;
    virtual bool isOpen() = 0;
    virtual bool okBtnClicked() = 0;
    virtual bool closeBtnClicked() = 0;
    virtual T getInput() = 0;
};

}

#endif