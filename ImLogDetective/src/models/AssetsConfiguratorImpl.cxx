
#include "models/AssetsConfiguratorImpl.h"
#include "ImLogDetectiveDefs.h"
#include <unistd.h>
#include <string>
#include <cstring>

namespace ImLogDetective
{

struct AssetsConfiguratorImpl::Impl
{
    Impl();
    ~Impl() = default;
    std::string currentModule;
    std::filesystem::path currentModulePath;
};

AssetsConfiguratorImpl::Impl::Impl() :
    currentModule(Common::MaxTextboxInputLength, '\0')
{
    if(readlink("/proc/self/exe", currentModule.data(), Common::MaxTextboxInputLength) > 0)
    {
        currentModulePath = std::filesystem::path{std::string(currentModule.data(), std::strlen(currentModule.data()))}.parent_path();
    }
}

AssetsConfiguratorImpl::AssetsConfiguratorImpl() :
    p{std::make_unique<Impl>()}
{
}

AssetsConfiguratorImpl::~AssetsConfiguratorImpl() = default;

std::filesystem::path AssetsConfiguratorImpl::getTtfFile(const std::string& fontName)
{
    return std::filesystem::path{};
}

std::filesystem::path AssetsConfiguratorImpl::getDefaultTtfFile()
{
    return p->currentModulePath / std::filesystem::path{Font::DefaultFontTffPath};
}

std::filesystem::path AssetsConfiguratorImpl::getIconFile()
{
    return p->currentModulePath / std::filesystem::path{Icons::ImLogDetectiveIcon};
}

}