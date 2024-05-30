
#include "models/AssetsConfigurator.h"
#include "ImLogDetectiveDefs.h"
#include <unistd.h>
#include <string>
#include <cstring>

namespace ImLogDetective
{

struct AssetsConfigurator::Impl
{
    Impl();
    ~Impl() = default;
    std::string currentModule;
    std::filesystem::path currentModulePath;
};

AssetsConfigurator::Impl::Impl() :
    currentModule(Common::MaxTextboxInputLength, '\0')
{
    if(readlink("/proc/self/exe", currentModule.data(), Common::MaxTextboxInputLength) > 0)
    {
        currentModulePath = std::filesystem::path{std::string(currentModule.data(), std::strlen(currentModule.data()))}.parent_path();
    }
}

AssetsConfigurator::AssetsConfigurator() :
    p{std::make_unique<Impl>()}
{
}

AssetsConfigurator::~AssetsConfigurator() = default;

std::filesystem::path AssetsConfigurator::getTtfFile(const std::string& fontName)
{
    return std::filesystem::path{};
}

std::filesystem::path AssetsConfigurator::getDefaultTtfFile()
{
    return p->currentModulePath / std::filesystem::path{Font::DefaultFontTffPath};
}

std::filesystem::path AssetsConfigurator::getIconFile()
{
    return p->currentModulePath / std::filesystem::path{Icons::ImLogDetectiveIcon};
}

}