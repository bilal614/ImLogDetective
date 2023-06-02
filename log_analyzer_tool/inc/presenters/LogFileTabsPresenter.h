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
    LogFileTabsPresenter(ILogFilePresenter& logFilePresenter, ILogDataModelFactory& logFilePresenterFactory, ITabBar& tabBar);
    ~LogFileTabsPresenter();
    void update(const std::filesystem::path& folderPath) override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};
}