#include "dearimgui/IOContextImpl.h"
#include "imgui.h"
#include "ImLogDetectiveDefs.h"

namespace ImLogDetective
{

struct IOContextImpl::Impl
{
    Impl();
    ~Impl() = default;
    ImGuiIO& io;
};

IOContextImpl::Impl::Impl() :
    io{ImGui::GetIO()}
{
}

IOContextImpl::IOContextImpl() :
    p{std::make_unique<Impl>()}
{
}

IOContextImpl::~IOContextImpl() = default;

void IOContextImpl::unsetIniFile()
{
    p->io.IniFilename = nullptr;
}

void IOContextImpl::setFontScale(const float scaleFactor)
{
    p->io.FontGlobalScale = scaleFactor;
}

bool IOContextImpl::setFontFromTtfFile(const std::filesystem::path& path)
{
    if(std::filesystem::exists(path) && 
        std::filesystem::is_regular_file(path) &&
        path.extension() == ".ttf")
    {
        p->io.Fonts->AddFontFromFileTTF(path.c_str(), Font::DefaultFontPixelSize);
    }
    return false;
}

}