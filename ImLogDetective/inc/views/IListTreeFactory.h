#pragma once

#include <memory>

namespace ImLogDetective
{

class IListTreeWidget;

class IListTreeFactory
{
public:
    virtual ~IListTreeFactory() = default;
    virtual std::unique_ptr<IListTreeWidget> createListTreeWidget() = 0;
};

}