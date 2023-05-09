#pragma once

#include <string>

namespace LogAnalyzerTool
{

struct ScopedImGuiWindow;

class IWindowFactory
{
public:
    virtual ~IWindowFactory() = default;
    virtual ScopedImGuiWindow createWindow() = 0;
    virtual ScopedImGuiWindow createChildWindow(const std::string& windowName) = 0;
};

}