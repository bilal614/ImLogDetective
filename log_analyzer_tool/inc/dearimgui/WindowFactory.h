#pragma once

#include "IWindowFactory.h"
#include <memory>

namespace LogAnalyzerTool
{
class IMainViewPort;

class WindowFactory : public IWindowFactory
{
    public:
        WindowFactory(const IMainViewPort& mainWindow);
        ~WindowFactory();
        std::unique_ptr<IScopedImGuiWindow> createWindow() override;
        std::unique_ptr<IScopedImGuiWindow> createChildWindow(const std::string& windowName) override;
    private:
        struct Impl;
        std::unique_ptr<Impl> p;
};

}