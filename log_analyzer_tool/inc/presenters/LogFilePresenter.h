#pragma once

#include <memory>
#include "presenters/ILogFilePresenter.h"
#include "views/ILogView.h"

namespace LogAnalyzerTool
{

class ILogDataModel;
class ILogFileParser;
class ILogFilterView;
class ILogView;
class IWindowFactory;

class LogFilePresenter : public ILogFilePresenter
{
public:
    LogFilePresenter(
        IWindowFactory& windowFactory,
        ILogFilterView& logFilterView, 
        ILogView& logView,
        ILogFileParser& logFileParser,
        ILogDataModel& logDataModel);
    ~LogFilePresenter();
    void update(const std::filesystem::path& filePath) override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};
}