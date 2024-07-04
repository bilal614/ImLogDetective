
#ifndef IMLOGDETECTIVE_VIEWS_LISTTREEFACTORY_H
#define IMLOGDETECTIVE_VIEWS_LISTTREEFACTORY_H

#include <memory>

namespace ImLogDetective
{

class IListTreeWidget;

class ListTreeFactory
{
public:
    virtual ~ListTreeFactory() = default;
    virtual std::unique_ptr<IListTreeWidget> createListTreeWidget() = 0;
};

}

#endif