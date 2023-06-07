#pragma once

#include <string>

namespace LogAnalyzerTool
{

class IListTreeWidget
{
public:
    virtual ~IListTreeWidget() = default;
    virtual void addNode(const std::string& nodeId) = 0;
};

}