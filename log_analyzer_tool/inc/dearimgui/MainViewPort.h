#pragma once

#include "IMainViewPort.h"
#include <memory>

namespace LogAnalyzerTool
{
class MainViewPort : public IMainViewPort 
{
public:
    MainViewPort();
    ~MainViewPort();
    ImVec2 getAreaSize() const override;
    ImVec2 getWorkAreaSize() const override;
    ImVec2 getViewportPosition() const override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}