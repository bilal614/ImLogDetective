#pragma once

#include <string>
#include "views/IPopup.h"

struct ImVec2;

namespace ImLogDetective
{

class IProtectedInputPopup : public IPopup<std::string>
{
public:
    virtual void setPrompt(const std::string& prompt) = 0;
};

}