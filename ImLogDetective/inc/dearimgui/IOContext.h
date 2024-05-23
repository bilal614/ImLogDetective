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
    void unsetIniFile() final;
    void setFontScale(const float scaleFactor) final;
    bool setFontFromTtfFile(const std::filesystem::path& path) final;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
    
};

}