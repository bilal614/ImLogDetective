#pragma once

#include "views/ILogView.h"
#include "views/ITextWidgetFactory.h"
#include "gmock/gmock.h"

namespace TestImLogDetective {

class LogViewMock : public ImLogDetective::ILogView 
{
public:
    MOCK_METHOD(void, drawLogLineText, (std::string_view logText, const ImLogDetective::TextColor& color));
};

}