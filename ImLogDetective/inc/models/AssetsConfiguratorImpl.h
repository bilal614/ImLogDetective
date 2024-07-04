

#ifndef IMLOGDETECTIVE_MODELS_ASSETCONFIGURATORIMPL_H
#define IMLOGDETECTIVE_MODELS_ASSETCONFIGURATORIMPL_H

#include "models/AssetsConfigurator.h"
#include <memory>

namespace ImLogDetective
{

class AssetsConfiguratorImpl : public AssetsConfigurator
{
public:
    AssetsConfiguratorImpl();
    ~AssetsConfiguratorImpl();
    std::filesystem::path getTtfFile(const std::string& fontName) final;
    std::filesystem::path getDefaultTtfFile() final;
    std::filesystem::path getIconFile() final;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}

#endif