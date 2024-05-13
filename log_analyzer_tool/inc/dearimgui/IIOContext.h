#pragma once

#include <memory>

namespace ImLogDetective
{

class IIOContext
{
public:
    virtual ~IIOContext() = default;
    virtual void unsetIniFile() = 0;
    virtual void setFontScale(const float scaleFactor) = 0;
};

}