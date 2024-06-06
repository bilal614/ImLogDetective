#pragma once

#include "dearimgui/IScopedImGuiWindow.h"
#include "views/IWidgetFactory.h"
#include "imgui.h"
#include <string>

namespace ImLogDetective
{

struct ScopedImGuiWindow : public IScopedImGuiWindow
{
    WindowType windowType;
    ImVec2 windowSize;
    ImVec2 windowPosition;
    IWidgetFactory& widgetFactory;

    WindowType getWindowType() override
    {
        return windowType;
    }

    ImVec2 getWindowPosition() override
    {
        return windowPosition;
    }

    ImVec2 getWindowSize() override
    {
        return windowSize;
    }

    void onSameLine() override
    {
        widgetFactory.onSameLine();
    }

    ScopedImGuiWindow(IWidgetFactory& widgetFactory, 
        const std::string& windowName, 
        const ImVec2& size, 
        const ImVec2& position, 
        bool* openClose, 
        ImGuiWindowFlags windowFlags,
        WindowType type) 
            : widgetFactory{widgetFactory}, windowType{type}, windowSize{size}, windowPosition{position}
    {
        if(windowType == WindowType::MainWindow)
        {
            ImGui::SetNextWindowPos(ImVec2(windowPosition.x, windowPosition.y), ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowSize(windowSize, ImGuiCond_FirstUseEver);
        }

        if(windowType == WindowType::MainWindow)
        {
            ImGui::Begin(windowName.c_str(), openClose, windowFlags | ImGuiWindowFlags_NoTitleBar);
        }
        if(windowType == WindowType::ChildWindow)
        {
            ImGui::BeginChild(windowName.c_str(), windowSize, true, windowFlags);
        }
    }

    ~ScopedImGuiWindow()
    {
        if(windowType == WindowType::MainWindow)
        {
            ImGui::End();
        }
        if(windowType == WindowType::ChildWindow)
        {
            ImGui::EndChild();
        }
    }
};

}