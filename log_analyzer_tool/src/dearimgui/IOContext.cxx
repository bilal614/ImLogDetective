#include "dearimgui/IOContext.h"
#include "imgui.h"

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

}