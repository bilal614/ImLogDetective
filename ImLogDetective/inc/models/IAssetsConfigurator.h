#pragma once

#include <filesystem>

namespace ImLogDetective
{

class IAssetsConfigurator
{
public:
    virtual ~IAssetsConfigurator() = default;
    virtual std::filesystem::path getTtfFile(const std::string& fontName) = 0;
    virtual std::filesystem::path getDefaultTtfFile() = 0;
    virtual std::filesystem::path getIconFile() = 0;
};

}