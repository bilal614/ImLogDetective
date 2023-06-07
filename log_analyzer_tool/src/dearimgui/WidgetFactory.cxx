#include "dearimgui/IMainViewPort.h"
#include "LogAnalyzerToolDefs.h"
#include "dearimgui/IScopedImGuiWindow.h"
#include "dearimgui/ListTreeWidget.h"
#include "dearimgui/ScopedImGuiWindow.hpp"
#include "dearimgui/WidgetFactory.h"
#include "imgui.h"

#include <unordered_map>

namespace LogAnalyzerTool
{

struct WidgetFactory::Impl
{
    Impl(const IMainViewPort& mainViewPort);
    ~Impl() = default;
    std::unique_ptr<IScopedImGuiWindow> addWindow();

    const IMainViewPort& mainViewPort;
    std::unique_ptr<bool> openCloseWidgetPresent;
    ImGuiWindowFlags mainWindowFlags;
    ImGuiWindowFlags childWindowFlags;

    std::unordered_map<TextColor, ImVec4> colorMap;

};

WidgetFactory::Impl::Impl(const IMainViewPort& mainWindow) :
    mainViewPort{mainWindow},
    openCloseWidgetPresent{nullptr},
    mainWindowFlags{0},
    childWindowFlags{0},
    colorMap{
        {TextColor::Red, ImVec4(1.0f, 0.0f, 0.0f, 1.0f)},
        {TextColor::Orange, ImVec4(1.0f, 0.5f, 0.0f, 1.0f)},
        {TextColor::Yellow, ImVec4(1.0f, 1.0f, 0.0f, 1.0f)},
        {TextColor::Green, ImVec4(0.0f, 1.0f, 0.0f, 1.0f)},
        {TextColor::White, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)},
    }
{
    mainWindowFlags = ImGuiWindowFlags_MenuBar |
                ImGuiWindowFlags_NoMove | 
                ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoCollapse;
    childWindowFlags = ImGuiWindowFlags_HorizontalScrollbar;
}

std::unique_ptr<IScopedImGuiWindow> WidgetFactory::Impl::addWindow()
{
    return std::make_unique<ScopedImGuiWindow>(LogAnalyzerToolApplicationName, 
        mainViewPort.getAreaSize(), 
        mainViewPort.getViewportPosition(), 
        openCloseWidgetPresent.get(), 
        mainWindowFlags,
        WindowType::MainWindow);
}

WidgetFactory::WidgetFactory(const IMainViewPort& mainWindow) :
    p{std::make_unique<Impl>(mainWindow)}
{

}

WidgetFactory::~WidgetFactory() = default;

std::unique_ptr<IScopedImGuiWindow> WidgetFactory::createWindow()
{
    return p->addWindow();
}

std::unique_ptr<IScopedImGuiWindow> WidgetFactory::createChildWindow(
    const std::string& windowName,
    const ImVec2& position,
    const ImVec2& size)
{
    return std::make_unique<ScopedImGuiWindow>(
        windowName, 
        size, 
        position, 
        p->openCloseWidgetPresent.get(),
        p->childWindowFlags,
        WindowType::ChildWindow
    );
}

void WidgetFactory::createUnformattedText(const std::string& text)
{
    ImGui::TextUnformatted(text.c_str());
}

void WidgetFactory::createTextColored(std::string_view text, const TextColor& color)
{
    auto textColor = p->colorMap.find(color);
    if(textColor != p->colorMap.end())
    {
        ImGui::TextColored(textColor->second, "%s", text.data());
    }
}

std::unique_ptr<IListTreeWidget> WidgetFactory::createListTreeWidget()
{
    return std::make_unique<ListTreeWidget>();
}

}