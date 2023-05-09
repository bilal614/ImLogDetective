#include "dearimgui/IMainViewPort.h"
#include "LogAnalyzerToolDefs.h"
#include "dearimgui/ScopedImGuiWindow.hpp"
#include "dearimgui/WindowFactory.h"


namespace LogAnalyzerTool
{
struct WindowFactory::Impl
{
    Impl(const IMainViewPort& mainViewPort);
    ~Impl() = default;
    ScopedImGuiWindow addWindow();

    const IMainViewPort& mainViewPort;
    std::unique_ptr<bool> openCloseWidgetPresent;
    ImGuiWindowFlags windowFlags;

};

WindowFactory::Impl::Impl(const IMainViewPort& mainWindow) :
    mainViewPort{mainWindow},
    openCloseWidgetPresent{nullptr},
    windowFlags{0}
{
    windowFlags = ImGuiWindowFlags_MenuBar |
                //ImGuiWindowFlags_NoMove | 
                ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoCollapse;
}

ScopedImGuiWindow WindowFactory::Impl::addWindow()
{
    return ScopedImGuiWindow{LogAnalyzerToolApplicationName, mainViewPort.getAreaSize(), mainViewPort.getViewportPosition(), openCloseWidgetPresent.get(), windowFlags};
}

WindowFactory::WindowFactory(const IMainViewPort& mainWindow) :
    p{std::make_unique<Impl>(mainWindow)}
{

}

WindowFactory::~WindowFactory() = default;

ScopedImGuiWindow WindowFactory::createWindow()
{
    return p->addWindow();
}

ScopedImGuiWindow WindowFactory::createChildWindow(const std::string& windowName)
{
    auto position = p->mainViewPort.getViewportPosition();
    auto windowOffset = 500;
    position.x + windowOffset;
    position.y + windowOffset;
    return ScopedImGuiWindow{windowName, p->mainViewPort.getAreaSize(), position, p->openCloseWidgetPresent.get(), p->windowFlags};
}

}