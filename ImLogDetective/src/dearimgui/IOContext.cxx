#include "dearimgui/IOContext.h"
#include "imgui.h"
#include "ImLogDetectiveDefs.h"

namespace ImLogDetective
{

struct IOContext::Impl
{
    Impl();
    ~Impl() = default;
    ImGuiIO& io;
};

IOContext::Impl::Impl() :
    io{ImGui::GetIO()}
{
}

IOContext::IOContext() :
    p{std::make_unique<Impl>()}
{
}

IOContext::~IOContext() = default;

void IOContext::unsetIniFile()
{
    p->io.IniFilename = nullptr;
}

void IOContext::setFontScale(const float scaleFactor)
{
    p->io.FontGlobalScale = scaleFactor;
}

bool IOContext::setFontFromTtfFile(const std::filesystem::path& path)
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