#pragma once

#include <functional>
#include <string>

namespace LogAnalyzerTool
{

class IListTreeWidget
{
public:
    virtual ~IListTreeWidget() = default;
    virtual void addNode(const std::string& nodeId, std::function<void()> nodeClickedCallback) = 0;
};

}