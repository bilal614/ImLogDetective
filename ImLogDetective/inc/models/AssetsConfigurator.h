
#ifndef IMLOGDETECTIVE_MODELS_ASSETCONFIGURATOR_H
#define IMLOGDETECTIVE_MODELS_ASSETCONFIGURATOR_H

#include <filesystem>

namespace ImLogDetective
{

class AssetsConfigurator
{
public:
    virtual ~AssetsConfigurator() = default;
    virtual std::filesystem::path getTtfFile(const std::string& fontName) = 0;
    virtual std::filesystem::path getDefaultTtfFile() = 0;
    virtual std::filesystem::path getIconFile() = 0;
};

}

#endif