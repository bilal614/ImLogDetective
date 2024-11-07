

#ifndef IMLOGDETECTIVE_DEARIMGUI_SCOPEDIMGUIWINDOWIMPL_H
#define IMLOGDETECTIVE_DEARIMGUI_SCOPEDIMGUIWINDOWIMPL_H

#include "dearimgui/ScopedImGuiWindow.h"
#include "views/WidgetFactory.h"
#include "imgui.h"
#include <string>

namespace ImLogDetective
{

struct ScopedImGuiWindowImplementation : public ScopedImGuiWindow {
    ImVec2 windowSize;
    ImVec2 windowPosition;
    WidgetFactory& widgetFactory;

    ScopedImGuiWindowImplementation(WidgetFactory& widgetFactory, 
        const ImVec2& size, 
        const ImVec2& position) :
        widgetFactory{widgetFactory}, windowSize{size}, windowPosition{position}
    {
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

}; 

template <WindowType wType>
struct ScopedImGuiWindowImpl : public ScopedImGuiWindowImplementation
{
    ScopedImGuiWindowImpl(WidgetFactory& widgetFactory, 
        const std::string& windowName, 
        const ImVec2& size, 
        const ImVec2& position, 
        bool* openClose, 
        ImGuiWindowFlags windowFlags) 
            : ScopedImGuiWindowImplementation(widgetFactory, size, position)
    {
            ImGui::SetNextWindowPos(ImVec2(windowPosition.x, windowPosition.y), ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowSize(windowSize, ImGuiCond_FirstUseEver);
            ImGui::Begin(windowName.c_str(), openClose, windowFlags | ImGuiWindowFlags_NoTitleBar);
    }

    ~ScopedImGuiWindowImpl()
    {
        ImGui::End();
    }
};

template<>
struct ScopedImGuiWindowImpl<WindowType::ChildWindow> : public ScopedImGuiWindowImplementation
{
    ScopedImGuiWindowImpl(WidgetFactory& widgetFactory, 
        const std::string& windowName, 
        const ImVec2& size, 
        const ImVec2& position, 
        bool* openClose, 
        ImGuiWindowFlags windowFlags) 
            : ScopedImGuiWindowImplementation(widgetFactory, size, position)
    {
        ImGui::BeginChild(windowName.c_str(), windowSize, true, windowFlags);
    }

    ~ScopedImGuiWindowImpl()
    {
        ImGui::EndChild();
    }
};


}

#endif