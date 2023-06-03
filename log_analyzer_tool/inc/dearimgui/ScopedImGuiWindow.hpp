#pragma once

#include "dearimgui/IScopedImGuiWindow.h"
#include "imgui.h"
#include <string>

namespace LogAnalyzerTool
{

struct ScopedImGuiWindow : public IScopedImGuiWindow
{
    WindowType windowType;
    ImVec2 windowSize;
    ImVec2 windowPosition;

    WindowType getWindowType()
    {
        return windowType;
    }

    ImVec2 getWindowPosition()
    {
        return windowPosition;
    }

    ImVec2 getWindowSize()
    {
        return windowSize;
    }

    ScopedImGuiWindow(const std::string& windowName, const ImVec2& size, const ImVec2& position, bool* openClose, ImGuiWindowFlags windowFlags, WindowType type) 
        : windowType{type}, windowSize{size}, windowPosition{position}
    {
        if(windowType == WindowType::MainWindow)
        {
            ImGui::SetNextWindowPos(ImVec2(windowPosition.x, windowPosition.y), ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowSize(windowSize, ImGuiCond_FirstUseEver);
        }

        if(windowType == WindowType::MainWindow)
        {
            ImGui::Begin(windowName.c_str(), openClose, windowFlags);
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