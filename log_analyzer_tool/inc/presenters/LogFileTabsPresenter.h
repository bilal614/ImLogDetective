#pragma once

#include <memory>
#include "presenters/ILogFileTabsPresenter.h"

namespace LogAnalyzerTool
{

class ILogFilePresenterFactory;
class ITabBar;

class LogFileTabsPresenter : public ILogFileTabsPresenter
{
public:
    LogFileTabsPresenter(ILogFilePresenterFactory& logFilePresenterFactory, ITabBar& tabBar);
    ~LogFileTabsPresenter();
    void update(const std::filesystem::path& folderPath) override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};
}