#pragma once

#include "IIOContext.h"
#include <memory>

namespace ImLogDetective
{

class IOContext : public IIOContext
{
public:
    IOContext();
    ~IOContext();
    void unsetIniFile();
    void setFontScale(const float scaleFactor);
private:
    struct Impl;
    std::unique_ptr<Impl> p;
    
};

}