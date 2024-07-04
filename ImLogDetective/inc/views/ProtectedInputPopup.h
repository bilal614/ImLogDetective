
#ifndef IMLOGDETECTIVE_VIEWS_PROTECTEDINPUTPOPUP_H
#define IMLOGDETECTIVE_VIEWS_PROTECTEDINPUTPOPUP_H

#include <string>
#include "views/Popup.h"

struct ImVec2;

namespace ImLogDetective
{

class ProtectedInputPopup : public Popup<std::string>
{
public:
    virtual void setPrompt(const std::string& prompt) = 0;
};

}

#endif