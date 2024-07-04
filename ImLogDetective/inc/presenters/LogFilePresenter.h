#pragma once

#include <memory>
#include "presenters/ILogFilePresenter.h"

namespace LogEventHandling 
{
    class IEventLoop;
}

namespace ImLogDetective
{

class ILogDataModel;
class ILogFileParser;
class LogFilterView;
class LogView;
class IImGuiTextFilterWrapper;
class WindowFactory;

class LogFilePresenter : public ILogFilePresenter
{
public:
    LogFilePresenter(
        WindowFactory& windowFactory,
        LogEventHandling::IEventLoop& eventLoop,
        LogFilterView& logFilterView, 
        LogView& logView,
        ILogFileParser& logFileParser,
        IImGuiTextFilterWrapper& textFilterWrapper);
    ~LogFilePresenter();
    void update(const std::filesystem::path& filePath,  bool readLogFile, ILogDataModel& logDataModel) override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};
}