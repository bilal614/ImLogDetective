
#ifndef IMLOGDETECTIVE_VIEWS_LISTTREEFACTORY_H
#define IMLOGDETECTIVE_VIEWS_LISTTREEFACTORY_H

#include <memory>

namespace ImLogDetective
{

class ListTreeWidget;

class ListTreeFactory
{
public:
    virtual ~ListTreeFactory() = default;
    virtual std::unique_ptr<ListTreeWidget> createListTreeWidget() = 0;
};

}

#endif