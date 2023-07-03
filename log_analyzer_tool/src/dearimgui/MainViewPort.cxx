#include "dearimgui/MainViewPort.h"
#include "LogAnalyzerToolDefs.h"
#include "dearimgui/IIOContext.h"
#include "imgui.h"

namespace LogAnalyzerTool
{

struct MainViewPort::Impl
{
    bool scaleFactorHasChanged(const float newScaleFactor);
    bool scaleFactorWithinLimits(const float scaleFactor);

    Impl(IIOContext& ioContext);
    const ImGuiViewport* imGuiViewport;
    IIOContext& ioContext;
    float viewportScaleFactor;
};

MainViewPort::Impl::Impl(IIOContext& ioContext) :
    imGuiViewport{ImGui::GetMainViewport()},
    ioContext{ioContext},
    viewportScaleFactor{Bounds::ScaleFactorLowerBound}
{
}

bool MainViewPort::Impl::scaleFactorHasChanged(const float newScaleFactor)
{
    return newScaleFactor > (viewportScaleFactor + Bounds::ScaleFactorChangeSensitivity) || 
        newScaleFactor < (viewportScaleFactor - Bounds::ScaleFactorChangeSensitivity);
}

bool MainViewPort::Impl::scaleFactorWithinLimits(const float scaleFactor)
{
    return scaleFactor >= Bounds::ScaleFactorLowerBound && scaleFactor <= Bounds::ScaleFactorUpperBound;
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
    if(p->scaleFactorHasChanged(scaleFactor) && p->scaleFactorWithinLimits(scaleFactor))
    {
        p->viewportScaleFactor = scaleFactor;
        p->ioContext.setFontScale(p->viewportScaleFactor );
    }
}

}