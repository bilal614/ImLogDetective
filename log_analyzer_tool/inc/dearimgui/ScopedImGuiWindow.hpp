#pragma once

#include "imgui.h"
#include <string>

namespace LogAnalyzerTool
{

enum class WindowType
{
    MainWindow,
    ChildWindow
};
struct ScopedImGuiWindow
{
    WindowType windowType;

    ScopedImGuiWindow(const std::string& windowName, const ImVec2& size, const ImVec2& position, bool* openClose, ImGuiWindowFlags windowFlags, WindowType type) 
        : windowType{type}
    {
        ImGui::SetNextWindowPos(ImVec2(position.x, position.y), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(size, ImGuiCond_FirstUseEver);

        if(windowType == WindowType::MainWindow)
        {
            ImGui::Begin(windowName.c_str(), openClose, windowFlags);
        }
        if(windowType == WindowType::ChildWindow)
        {
            ImGui::BeginChild(windowName.c_str(), size, true, windowFlags);
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