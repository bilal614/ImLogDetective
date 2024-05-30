#pragma once

#include "IAssetsConfigurator.h"
#include <memory>

namespace ImLogDetective
{

class AssetsConfigurator : public IAssetsConfigurator
{
public:
    AssetsConfigurator();
    ~AssetsConfigurator();
    std::filesystem::path getTtfFile(const std::string& fontName) final;
    std::filesystem::path getDefaultTtfFile() final;
    std::filesystem::path getIconFile() final;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}