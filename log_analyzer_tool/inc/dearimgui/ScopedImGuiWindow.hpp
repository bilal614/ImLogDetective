#pragma once

#include "imgui.h"
#include <string>

#include <iostream>

namespace LogAnalyzerTool
{
struct ScopedImGuiWindow
{
    ScopedImGuiWindow(const std::string& windowName, const ImVec2& size, const ImVec2& position, bool* openClose, ImGuiWindowFlags windowFlags)
    {
        std::cout << "Window size: x=" << size.x << ", y=" << size.y << ", Window position: x=" << position.x << ", y=" << position.y << std::endl;
        ImGui::SetNextWindowPos(ImVec2(position.x+500, position.y+300), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(size, ImGuiCond_FirstUseEver);
        ImGui::Begin(windowName.c_str(), openClose, windowFlags);
    }

    ~ScopedImGuiWindow()
    {
        ImGui::End();
    }
};

}