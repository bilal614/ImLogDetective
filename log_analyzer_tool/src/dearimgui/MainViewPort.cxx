#include "dearimgui/MainViewPort.h"
#include "imgui.h"

namespace LogAnalyzerTool
{
struct MainViewPort::Impl
{
    Impl();
    const ImGuiViewport* imGuiViewport;
};

MainViewPort::Impl::Impl() :
    imGuiViewport{ImGui::GetMainViewport()}
{
}

MainViewPort::MainViewPort() :
    p{std::make_unique<Impl>()}
{
}

MainViewPort::~MainViewPort() = default;

ImVec2 MainViewPort::getAreaSize() const
{
    // return ImGui::GetWindowSize();

    if(p->imGuiViewport != nullptr)
    {
        return p->imGuiViewport->Size;
    }
    return ImVec2{};
}

ImVec2 MainViewPort::getWorkAreaSize() const
{
    if(p->imGuiViewport != nullptr)
    {
        return p->imGuiViewport->WorkSize;
    }
    return ImVec2{};
}

ImVec2 MainViewPort::getViewportPosition() const
{
    //return ImGui::GetWindowPos();
    if(p->imGuiViewport != nullptr)
    {
        return p->imGuiViewport->Pos;
    }
    return ImVec2{};
}

ImVec2 MainViewPort::getViewportCenter() const
{
    return p->imGuiViewport->GetCenter();
}

}