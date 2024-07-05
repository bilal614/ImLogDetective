#pragma once

#include "presenters/LogFileTabsPresenter.h"
// #include "models/LogDataModel.h"
#include "EventHandling/IEvent.h"
#include "gmock/gmock.h"

namespace TestImLogDetective {

class LogFileTabsPresenterMock : public ImLogDetective::LogFileTabsPresenter 
{
public:
    MOCK_METHOD(void, update, (const std::vector<std::filesystem::path>& filePaths));
    MOCK_METHOD(LogEventHandling::IEvent<const std::string&>&, getTabsOpenedEvent, ());
};

}