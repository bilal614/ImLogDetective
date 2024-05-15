#pragma once

#include "views/ILogView.h"
#include "views/ITextWidgetFactory.h"
#include "gmock/gmock.h"
#include "models/LogData.h"


namespace TestImLogDetective {

class LogViewMock : public ImLogDetective::ILogView 
{
public:
    MOCK_METHOD(void, drawLogLineText, (ImLogDetective::LogData& logLine, const ImLogDetective::TextColor& color));
};

}