
#ifndef IMLOGDETECTIVE_VIEWS_WINDOWFACTORY_H
#define IMLOGDETECTIVE_VIEWS_WINDOWFACTORY_H


#include "dearimgui/ScopedImGuiWindow.h"
#include <memory>
#include <string>

struct ImVec2;

namespace ImLogDetective
{

class WindowFactory
{
public:
    virtual ~WindowFactory() = default;
    virtual std::unique_ptr<ScopedImGuiWindow> createWindow() = 0;
    virtual std::unique_ptr<ScopedImGuiWindow> createChildWindow(
        const std::string& windowName, 
        const ImVec2& position,
        const ImVec2& size) = 0;
};

}

#endif