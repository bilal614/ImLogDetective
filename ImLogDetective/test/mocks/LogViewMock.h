
#ifndef IMLOGDETECTIVE_VIEWS_LOGVIEWMOCK_H
#define IMLOGDETECTIVE_VIEWS_LOGVIEWMOCK_H

#include "views/LogView.h"
#include "models/LogLine.h"
#include <gmock/gmock.h>


namespace TestImLogDetective {

class LogViewMock : public ImLogDetective::LogView 
{
public:
    MOCK_METHOD(void, drawLogLineText, (ImLogDetective::LogLine& logLine));
};

}

#endif