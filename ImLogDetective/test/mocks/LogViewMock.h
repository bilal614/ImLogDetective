#pragma once

#include "views/ILogView.h"
#include "models/LogLine.h"
#include <gmock/gmock.h>


namespace TestImLogDetective {

class LogViewMock : public ImLogDetective::ILogView 
{
public:
    MOCK_METHOD(void, drawLogLineText, (ImLogDetective::LogLine& logLine));
};

}