#include "dearimgui/IMainViewPort.h"
#include "LogAnalyzerToolDefs.h"
#include "dearimgui/IScopedImGuiWindow.h"
#include "dearimgui/ScopedImGuiWindow.hpp"
#include "dearimgui/WindowFactory.h"
#include "imgui.h"


namespace LogAnalyzerTool
{
struct WindowFactory::Impl
{
    Impl(const IMainViewPort& mainViewPort);
    ~Impl() = default;
    std::unique_ptr<IScopedImGuiWindow> addWindow();

    const IMainViewPort& mainViewPort;
    std::unique_ptr<bool> openCloseWidgetPresent;
    ImGuiWindowFlags mainWindowFlags;
    ImGuiWindowFlags childWindowFlags;

};

WindowFactory::Impl::Impl(const IMainViewPort& mainWindow) :
    mainViewPort{mainWindow},
    openCloseWidgetPresent{nullptr},
    mainWindowFlags{0},
    childWindowFlags{0}
{
    mainWindowFlags = ImGuiWindowFlags_MenuBar |
                ImGuiWindowFlags_NoMove | 
                ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoCollapse;
    childWindowFlags = ImGuiWindowFlags_HorizontalScrollbar;
}

std::unique_ptr<IScopedImGuiWindow> WindowFactory::Impl::addWindow()
{
    return std::make_unique<ScopedImGuiWindow>(LogAnalyzerToolApplicationName, 
        mainViewPort.getAreaSize(), 
        mainViewPort.getViewportPosition(), 
        openCloseWidgetPresent.get(), 
        mainWindowFlags,
        WindowType::MainWindow);
}

WindowFactory::WindowFactory(const IMainViewPort& mainWindow) :
    p{std::make_unique<Impl>(mainWindow)}
{

}

WindowFactory::~WindowFactory() = default;

std::unique_ptr<IScopedImGuiWindow> WindowFactory::createWindow()
{
    return p->addWindow();
}

std::unique_ptr<IScopedImGuiWindow> WindowFactory::createChildWindow(const std::string& windowName)
{
    auto position = ImVec2{0, 0};
    auto size = ImVec2{0, 0};
    return std::make_unique<ScopedImGuiWindow>(
        windowName, 
        size, 
        position, 
        p->openCloseWidgetPresent.get(),
        p->childWindowFlags,
        WindowType::ChildWindow
    );
}

}