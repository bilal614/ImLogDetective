
#include "models/FontConfigurator.h"
#include "ImLogDetectiveDefs.h"
#include <unistd.h>
#include <string>
#include <cstring>

namespace ImLogDetective
{

struct FontConfigurator::Impl
{
    Impl();
    ~Impl() = default;
    std::string currentModule;
    std::filesystem::path currentModulePath;
};

FontConfigurator::Impl::Impl() :
    currentModule(Common::MaxTextboxInputLength, '\0')
{
    if(readlink("/proc/self/exe", currentModule.data(), Common::MaxTextboxInputLength) > 0)
    {
        currentModulePath = std::filesystem::path{std::string(currentModule.data(), std::strlen(currentModule.data()))}.parent_path();
    }
}

FontConfigurator::FontConfigurator() :
    p{std::make_unique<Impl>()}
{
}

FontConfigurator::~FontConfigurator() = default;

std::filesystem::path FontConfigurator::getTtfFile(const std::string& fontName)
{
    return std::filesystem::path{};
}

std::filesystem::path FontConfigurator::getDefaultTtfFile()
{
    return p->currentModulePath / std::filesystem::path{Font::DefaultFontTffPath};
}

}