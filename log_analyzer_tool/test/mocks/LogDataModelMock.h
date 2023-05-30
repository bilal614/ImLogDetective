#pragma once

#include "models/ILogDataModel.h"
#include "gmock/gmock.h"
#include <string>
#include <vector>

namespace TestLogAnalyzerTool {

class LogDataModelMock : public LogAnalyzerTool::ILogDataModel 
{
public:
    MOCK_METHOD(void, addLogData, (std::string dataLine)); 
    MOCK_METHOD(const std::vector<LogAnalyzerTool::LogData>&, getLogData, ());
};

}