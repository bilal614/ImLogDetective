#pragma once

#include "IWindowFactory.h"
#include <memory>

namespace LogAnalyzerTool
{
class IMainViewPort;
struct ScopedImGuiWindow;

class WindowFactory : public IWindowFactory
{
    public:
        WindowFactory(const IMainViewPort& mainWindow);
        ~WindowFactory();
        ScopedImGuiWindow createWindow() override;
        ScopedImGuiWindow createChildWindow(const std::string& windowName) override;
    private:
        struct Impl;
        std::unique_ptr<Impl> p;
};

}