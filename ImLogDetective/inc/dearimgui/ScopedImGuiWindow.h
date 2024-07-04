
#ifndef IMLOGDETECTIVE_DEARIMGUI_SCOPEDIMGUIWINDOW_H
#define IMLOGDETECTIVE_DEARIMGUI_SCOPEDIMGUIWINDOW_H

#include <string>

struct ImVec2;

namespace ImLogDetective
{

enum class WindowType
{
    MainWindow,
    ChildWindow
};

struct ScopedImGuiWindow
{
    virtual ~ScopedImGuiWindow() = default;
    virtual WindowType getWindowType() = 0;
    virtual ImVec2 getWindowPosition() = 0;
    virtual ImVec2 getWindowSize() = 0;
    virtual void onSameLine() = 0;
};

}

#endif