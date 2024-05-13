#pragma once

#include "dearimgui/IScopedImGuiWindow.h"
#include <memory>
#include <string>

struct ImVec2;

namespace ImLogDetective
{

class IWindowFactory
{
public:
    virtual ~IWindowFactory() = default;
    virtual std::unique_ptr<IScopedImGuiWindow> createWindow() = 0;
    virtual std::unique_ptr<IScopedImGuiWindow> createChildWindow(
        const std::string& windowName, 
        const ImVec2& position,
        const ImVec2& size) = 0;
};

}