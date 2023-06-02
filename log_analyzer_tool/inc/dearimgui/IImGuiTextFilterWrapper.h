#pragma once
#include <string>

namespace LogAnalyzerTool
{

class IImGuiTextFilterWrapper
{
public:
    virtual ~IImGuiTextFilterWrapper() = default;
    virtual void draw() = 0;
    virtual bool isActive() const = 0;
    virtual bool passFilter(std::string_view text) = 0;
};

}