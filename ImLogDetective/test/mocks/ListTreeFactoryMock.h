

#ifndef IMLOGDETECTIVE_VIEWS_LISTTREEFACTORYMOCK_H
#define IMLOGDETECTIVE_VIEWS_LISTTREEFACTORYMOCK_H

#include "views/ListTreeFactory.h"
#include "ListTreeWidgetMock.h"
#include "gmock/gmock.h"

namespace ImLogDetective
{

class ListTreeFactoryMock : public ListTreeFactory
{
public:
    MOCK_METHOD(std::unique_ptr<ListTreeWidget>, createListTreeWidget,());
};

}

#endif