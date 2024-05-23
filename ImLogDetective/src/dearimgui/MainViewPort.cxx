#include "dearimgui/MainViewPort.h"
#include "ImLogDetectiveDefs.h"
#include "dearimgui/IIOContext.h"
#include "imgui.h"

namespace ImLogDetective
{

struct MainViewPort::Impl
{
    bool scaleFactorWithinLimits(const float scaleFactor);

    Impl(IIOContext& ioContext);
    const ImGuiViewport* imGuiViewport;
    IIOContext& ioContext;
    float viewportScaleFactor;
};

MainViewPort::Impl::Impl(IIOContext& ioContext) :
    imGuiViewport{ImGui::GetMainViewport()},
    ioContext{ioContext},
    viewportScaleFactor{Scaling::ScaleFactorLowerBound}
{
}

bool MainViewPort::Impl::scaleFactorWithinLimits(const float scaleFactor)
{
    return scaleFactor >= Scaling::ScaleFactorLowerBound && scaleFactor <= Scaling::ScaleFactorUpperBound;
}

MainViewPort::MainViewPort(IIOContext& ioContext) :
    p{std::make_unique<Impl>(ioContext)}
{
}

MainViewPort::~MainViewPort() = default;

ImVec2 MainViewPort::getAreaSize() const
{
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

void MainViewPort::setViewportScale(const float scaleFactor)
{
    if(scaleFactor > (p->viewportScaleFactor + LayoutBounds::ScaleFactorChangeSensitivity) ||
        scaleFactor < (p->viewportScaleFactor - LayoutBounds::ScaleFactorChangeSensitivity))
    {
        if(p->scaleFactorWithinLimits(scaleFactor))
        {
            p->viewportScaleFactor = scaleFactor;
            p->ioContext.setFontScale(p->viewportScaleFactor);
        }
    }
}

}