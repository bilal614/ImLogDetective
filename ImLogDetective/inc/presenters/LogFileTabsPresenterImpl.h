
#ifndef IMLOGDETECTIVE_PRESENTERS_LOGFILETABSPRESENTERIMPL_H
#define IMLOGDETECTIVE_PRESENTERS_LOGFILETABSPRESENTERIMPL_H

#include <memory>
#include "presenters/LogFileTabsPresenter.h"

namespace ImLogDetective
{

class LogFilePresenter;
class LogDataModelFactory;
class TabBar;

class LogFileTabsPresenterImpl : public LogFileTabsPresenter
{
public:
    LogFileTabsPresenterImpl(
        LogFilePresenter&, 
        LogDataModelFactory&, 
        TabBar&,
        std::unique_ptr<LogEventHandling::IEvent<const std::string&>>);
    ~LogFileTabsPresenterImpl();
    void update(const std::vector<std::filesystem::path>& filePaths) override;
    LogEventHandling::IEvent<const std::string&>& getTabsOpenedEvent() override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}

#endif