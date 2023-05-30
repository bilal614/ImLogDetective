#pragma once

#include <string>

namespace LogAnalyzerTool
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
};

}