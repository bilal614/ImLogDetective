#pragma once

#include "presenters/ILogFileTabsPresenter.h"
#include "models/ILogDataModel.h"
#include "event_handling/IEvent.h"
#include "gmock/gmock.h"

namespace TestLogAnalyzerTool {

class LogFileTabsPresenterMock : public LogAnalyzerTool::ILogFileTabsPresenter 
{
public:
    MOCK_METHOD(void, update, (const std::vector<std::filesystem::path>& filePaths));
    MOCK_METHOD(LogAnalyzerTool::IEvent<const std::string&>&, getTabsOpenedEvent, ());
};

}