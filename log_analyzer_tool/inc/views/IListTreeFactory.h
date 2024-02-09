#pragma once

#include <memory>

namespace LogAnalyzerTool
{

class IListTreeWidget;

class IListTreeFactory
{
public:
    virtual ~IListTreeFactory() = default;
    virtual std::unique_ptr<IListTreeWidget> createListTreeWidget() = 0;
};

}