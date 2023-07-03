#pragma once

#include "event_handling/IEvent.h"
#include <filesystem>
#include <vector>

namespace LogAnalyzerTool
{
class ILogFileTabsPresenter
{
public:
    virtual ~ILogFileTabsPresenter() = default;
    virtual void update(const std::vector<std::filesystem::path>& filePaths) = 0;
    virtual IEvent<const std::string&>& getTabsOpenedEvent() = 0;
};

}