#pragma once
#include "dearimgui/IImGuiTextFilterWrapper.h"
#include <memory>

namespace LogAnalyzerTool
{

class ImGuiTextFilterWrapper : public IImGuiTextFilterWrapper 
{
public:
    ImGuiTextFilterWrapper(const std::string& label, float width);
    ~ImGuiTextFilterWrapper();
    void draw() override;
    bool isActive() const override;
    bool passFilter(std::string_view text) override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}