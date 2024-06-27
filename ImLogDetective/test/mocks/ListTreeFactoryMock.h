#pragma once

#include "views/IListTreeFactory.h"
#include "ListTreeWidgetMock.h"
#include "gmock/gmock.h"

namespace ImLogDetective
{

class ListTreeFactoryMock : public IListTreeFactory
{
public:
    MOCK_METHOD(std::unique_ptr<IListTreeWidget>, createListTreeWidget,());
};

}