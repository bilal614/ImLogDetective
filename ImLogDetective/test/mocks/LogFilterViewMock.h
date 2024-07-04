
#ifndef IMLOGDETECTIVE_VIEWS_LOGFILTERVIEWMOCK_H
#define IMLOGDETECTIVE_VIEWS_LOGFILTERVIEWMOCK_H

#include "views/LogFilterView.h"
#include "gmock/gmock.h"

namespace TestImLogDetective {

class LogFilterViewMock : public ImLogDetective::LogFilterView 
{
public:
    MOCK_METHOD(void, drawFilterCheckBoxes, (), (const));
    MOCK_METHOD(bool, getDebugChecked, (), (const));
    MOCK_METHOD(bool, getInfoChecked, () ,(const));
    MOCK_METHOD(bool, getWarningChecked, (), (const));
    MOCK_METHOD(bool, getErrorChecked,(), (const));
};

}

#endif