
#ifndef IMLOGDETECTIVE_PRESENTERS_LOGFILETABSPRESENTER_H
#define IMLOGDETECTIVE_PRESENTERS_LOGFILETABSPRESENTER_H

#include "EventHandling/IEvent.h"
#include <filesystem>
#include <vector>

namespace ImLogDetective
{
class LogFileTabsPresenter
{
public:
    virtual ~LogFileTabsPresenter() = default;
    virtual void update(const std::vector<std::filesystem::path>& filePaths) = 0;
    virtual LogEventHandling::IEvent<const std::string&>& getTabsOpenedEvent() = 0;
};

}

#endif