#pragma once

#include "views/ILogFilterView.h"
#include "gmock/gmock.h"

namespace TestLogAnalyzerTool {

class LogFilterViewMock : public LogAnalyzerTool::ILogFilterView 
{
public:
    MOCK_METHOD(void, drawFilterCheckBoxes, (), (const));
    MOCK_METHOD(bool, getDebugChecked, (), (const));
    MOCK_METHOD(bool, getInfoChecked, () ,(const));
    MOCK_METHOD(bool, getWarningChecked, (), (const));
    MOCK_METHOD(bool, getErrorChecked,(), (const));
};

}