

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
    ImGuiWidgetWrapper& imGuiWidgetWrapper;

    ScopedImGuiWindowImplementation(ImGuiWidgetWrapper& imGuiWidgetWrapper, 
        const ImVec2& size, 
        const ImVec2& position) :
        imGuiWidgetWrapper{imGuiWidgetWrapper}, windowSize{size}, windowPosition{position}
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
        imGuiWidgetWrapper.sameLine();
    }

}; 

template <WindowType wType>
struct ScopedImGuiWindowImpl : public ScopedImGuiWindowImplementation
{
    ScopedImGuiWindowImpl(ImGuiWidgetWrapper& imGuiWidgetWrapper, 
        const std::string& windowName, 
        const ImVec2& size, 
        const ImVec2& position, 
        bool* openClose, 
        ImGuiWindowFlags windowFlags) 
            : ScopedImGuiWindowImplementation(imGuiWidgetWrapper, size, position)
    {
        imGuiWidgetWrapper.setNextWindowPosAndSize(position, windowSize);
        imGuiWidgetWrapper.windowBegin(windowName, openClose, windowFlags);
    }

    ~ScopedImGuiWindowImpl()
    {
        imGuiWidgetWrapper.windowEnd();
    }
};

template<>
struct ScopedImGuiWindowImpl<WindowType::ChildWindow> : public ScopedImGuiWindowImplementation
{
    ScopedImGuiWindowImpl(ImGuiWidgetWrapper& imGuiWidgetWrapper, 
        const std::string& windowName, 
        const ImVec2& size, 
        const ImVec2& position, 
        bool* openClose, 
        ImGuiWindowFlags windowFlags) 
            : ScopedImGuiWindowImplementation(imGuiWidgetWrapper, size, position)
    {
        imGuiWidgetWrapper.childWindowBegin(windowName, windowSize, windowFlags);
    }

    ~ScopedImGuiWindowImpl()
    {
        imGuiWidgetWrapper.childWindowEnd();
    }
};


}

#endif