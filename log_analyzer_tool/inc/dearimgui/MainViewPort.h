#pragma once

#include "IMainViewPort.h"
#include <memory>

namespace LogAnalyzerTool
{
class IIOContext;

class MainViewPort : public IMainViewPort 
{
public:
    MainViewPort(IIOContext& ioContext);
    ~MainViewPort();
    ImVec2 getAreaSize() const override;
    ImVec2 getWorkAreaSize() const override;
    ImVec2 getViewportPosition() const override;
    ImVec2 getViewportCenter() const override;
    void setViewportScale(const float scaleFactor) override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}