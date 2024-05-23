#pragma once

#include "IFontConfigurator.h"
#include <memory>

namespace ImLogDetective
{

class FontConfigurator : public IFontConfigurator
{
public:
    FontConfigurator();
    ~FontConfigurator();
    std::filesystem::path getTtfFile(const std::string& fontName) final;
    std::filesystem::path getDefaultTtfFile() final;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}