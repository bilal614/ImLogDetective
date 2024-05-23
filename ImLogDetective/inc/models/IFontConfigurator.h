#pragma once

#include <filesystem>

namespace ImLogDetective
{

class IFontConfigurator
{
public:
    virtual ~IFontConfigurator() = default;
    virtual std::filesystem::path getTtfFile(const std::string& fontName) = 0;
    virtual std::filesystem::path getDefaultTtfFile() = 0;
};

}