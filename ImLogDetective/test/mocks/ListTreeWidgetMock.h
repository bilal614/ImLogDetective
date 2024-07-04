#pragma once

#include "dearimgui/ListTreeWidget.h"
#include "gmock/gmock.h"
#include <functional>
#include <string>

namespace ImLogDetective
{

class ListTreeWidgetMock : public ListTreeWidget
{
public:
    MOCK_METHOD(void, addNode,(const std::string&, std::function<void()>));
};

}