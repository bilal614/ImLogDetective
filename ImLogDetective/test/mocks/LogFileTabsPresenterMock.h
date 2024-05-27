#pragma once

#include "presenters/ILogFileTabsPresenter.h"
#include "models/ILogDataModel.h"
#include "EventHandling/IEvent.h"
#include "gmock/gmock.h"

namespace TestImLogDetective {

class LogFileTabsPresenterMock : public ImLogDetective::ILogFileTabsPresenter 
{
public:
    MOCK_METHOD(void, update, (const std::vector<std::filesystem::path>& filePaths));
    MOCK_METHOD(LogEventHandling::IEvent<const std::string&>&, getTabsOpenedEvent, ());
};

}