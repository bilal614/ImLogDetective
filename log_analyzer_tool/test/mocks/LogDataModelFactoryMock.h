#pragma once

#include "presenters/ILogDataModelFactory.h"
#include "gmock/gmock.h"
#include <string>
#include <vector>

namespace TestLogAnalyzerTool {

class LogDataModelFactoryMock : public LogAnalyzerTool::ILogDataModelFactory 
{
public:
    MOCK_METHOD(std::unique_ptr<LogAnalyzerTool::ILogDataModel>, createLogFilePresenter, (const std::string&));
};

}