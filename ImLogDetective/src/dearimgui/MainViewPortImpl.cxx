#include "dearimgui/MainViewPortImpl.h"
#include "ImLogDetectiveDefs.h"
#include "dearimgui/IOContext.h"
#include "imgui.h"

namespace ImLogDetective
{

struct MainViewPortImpl::Impl
{
    bool scaleFactorWithinLimits(const float scaleFactor);

    Impl(IOContext& ioContext);
    const ImGuiViewport* imGuiViewport;
    IOContext& ioContext;
    float viewportScaleFactor;
};

MainViewPortImpl::Impl::Impl(IOContext& ioContext) :
    imGuiViewport{ImGui::GetMainViewport()},
    ioContext{ioContext},
    viewportScaleFactor{Scaling::ScaleFactorLowerBound}
{
}

bool MainViewPortImpl::Impl::scaleFactorWithinLimits(const float scaleFactor)
{
    return scaleFactor >= Scaling::ScaleFactorLowerBound && scaleFactor <= Scaling::ScaleFactorUpperBound;
}

MainViewPortImpl::MainViewPortImpl(IOContext& ioContext) :
    p{std::make_unique<Impl>(ioContext)}
{
}

MainViewPortImpl::~MainViewPortImpl() = default;

ImVec2 MainViewPortImpl::getAreaSize() const
{
    if(p->imGuiViewport != nullptr)
    {
        return p->imGuiViewport->Size;
    }
    return ImVec2{};
}

ImVec2 MainViewPortImpl::getWorkAreaSize() const
{
    if(p->imGuiViewport != nullptr)
    {
        return p->imGuiViewport->WorkSize;
    }
    return ImVec2{};
}

ImVec2 MainViewPortImpl::getViewportPosition() const
{
    if(p->imGuiViewport != nullptr)
    {
        return p->imGuiViewport->Pos;
    }
    return ImVec2{};
}

ImVec2 MainViewPortImpl::getViewportCenter() const
{
    return p->imGuiViewport->GetCenter();
}

void MainViewPortImpl::setViewportScale(const float scaleFactor)
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