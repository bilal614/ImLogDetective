#pragma once

#include <memory>
#include "presenters/ILogFilePresenter.h"
#include "views/ILogView.h"

namespace LogEventHandling 
{
    class IEventLoop;
}

namespace LogAnalyzerTool
{

class ILogDataModel;
class ILogFileParser;
class ILogFilterView;
class ILogView;
class IImGuiTextFilterWrapper;
class IWindowFactory;

class LogFilePresenter : public ILogFilePresenter
{
public:
    LogFilePresenter(
        IWindowFactory& windowFactory,
        LogEventHandling::IEventLoop& eventLoop,
        ILogFilterView& logFilterView, 
        ILogView& logView,
        ILogFileParser& logFileParser,
        IImGuiTextFilterWrapper& textFilterWrapper);
    ~LogFilePresenter();
    void update(const std::filesystem::path& filePath,  bool readLogFile, ILogDataModel& logDataModel) override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};
}