#pragma once

#include <string>

struct ImVec2;

namespace ImLogDetective
{

enum class WindowType
{
    MainWindow,
    ChildWindow
};

struct IScopedImGuiWindow
{
    virtual ~IScopedImGuiWindow() = default;
    virtual WindowType getWindowType() = 0;
    virtual ImVec2 getWindowPosition() = 0;
    virtual ImVec2 getWindowSize() = 0;
    virtual void onSameLine() = 0;
};

}