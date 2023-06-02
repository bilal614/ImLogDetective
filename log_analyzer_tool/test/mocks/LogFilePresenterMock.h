#pragma once

#include "presenters/ILogFilePresenter.h"
#include "models/ILogDataModel.h"
#include "gmock/gmock.h"

namespace TestLogAnalyzerTool {

class LogFilePresenterMock : public LogAnalyzerTool::ILogFilePresenter 
{
public:
    MOCK_METHOD(void, update, (const std::filesystem::path&, bool, LogAnalyzerTool::ILogDataModel&));
};

}