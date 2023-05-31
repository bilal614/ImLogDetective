#pragma once

#include "presenters/ILogFilePresenterFactory.h"
#include "presenters/ILogFilePresenter.h"

#include "gmock/gmock.h"
#include <string>
#include <vector>

namespace TestLogAnalyzerTool {

class LogFilePresenterFactoryMock : public LogAnalyzerTool::ILogFilePresenterFactory 
{
public:
    MOCK_METHOD(std::unique_ptr<LogAnalyzerTool::ILogFilePresenter>, createLogFilePresenter, (const std::filesystem::path& filePath));
};

}