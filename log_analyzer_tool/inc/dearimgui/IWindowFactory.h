#pragma once

#include "dearimgui/IScopedImGuiWindow.h"
#include <memory>
#include <string>

namespace LogAnalyzerTool
{

class IWindowFactory
{
public:
    virtual ~IWindowFactory() = default;
    virtual std::unique_ptr<IScopedImGuiWindow> createWindow() = 0;
    virtual std::unique_ptr<IScopedImGuiWindow> createChildWindow(const std::string& windowName) = 0;
};

}