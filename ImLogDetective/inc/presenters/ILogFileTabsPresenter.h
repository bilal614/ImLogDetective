#pragma once

#include "EventHandling/IEvent.h"
#include <filesystem>
#include <vector>

namespace ImLogDetective
{
class ILogFileTabsPresenter
{
public:
    virtual ~ILogFileTabsPresenter() = default;
    virtual void update(const std::vector<std::filesystem::path>& filePaths) = 0;
    virtual LogEventHandling::IEvent<const std::string&>& getTabsOpenedEvent() = 0;
};

}