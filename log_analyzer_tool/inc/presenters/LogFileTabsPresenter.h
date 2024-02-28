#pragma once

#include <memory>
#include "presenters/ILogFileTabsPresenter.h"

namespace LogAnalyzerTool
{

class ILogFilePresenter;
class ILogDataModelFactory;
class ITabBar;

class LogFileTabsPresenter : public ILogFileTabsPresenter
{
public:
    LogFileTabsPresenter(
        ILogFilePresenter&, 
        ILogDataModelFactory&, 
        ITabBar&,
        std::unique_ptr<LogEventHandling::IEvent<const std::string&>>);
    ~LogFileTabsPresenter();
    void update(const std::vector<std::filesystem::path>& filePaths) override;
    LogEventHandling::IEvent<const std::string&>& getTabsOpenedEvent() override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};
}