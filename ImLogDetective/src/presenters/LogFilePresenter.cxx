#include "presenters/LogFilePresenter.h"
#include "ImLogDetectiveDefs.h"
#include "dearimgui/ImGuiTextFilterWrapper.h"
#include "views/WindowFactory.h"
#include "models/LogFileParser.h"
#include "models/LogLine.h"
#include "EventHandling/Event.hpp"
#include "EventHandling/IEventLoop.h"
#include "models/LogDataModel.h"
#include "views/LogView.h"
#include "views/LogFilterView.h"
#include "imgui.h"

namespace ImLogDetective
{

struct LogFilePresenter::Impl
{
    Impl(WindowFactory& windowFactory,
        LogEventHandling::IEventLoop& eventLoop,
        LogFilterView& logFilterView, 
        LogView& logView,
        LogFileParser& logFileParser,
        ImGuiTextFilterWrapper& textFilterWrapper);
    ~Impl() = default;
    bool checkLogLineFiltered(const LogLine& line);
    void updateLogData(const std::filesystem::path& filePath, bool readLogFile, LogDataModel& logDataModel);

    WindowFactory& windowFactory;
    LogEventHandling::IEventLoop& eventLoop;
    LogFilterView& logFilterView;
    LogView& logView;
    LogFileParser& logFileParser;
    ImGuiTextFilterWrapper& textFilterWrapper;
};

LogFilePresenter::Impl::Impl(
    WindowFactory& windowFactory,
    LogEventHandling::IEventLoop& eventLoop,
    LogFilterView& logFilterView, 
    LogView& logView,
    LogFileParser& logFileParser,
    ImGuiTextFilterWrapper& textFilterWrapper) :
        windowFactory{windowFactory},
        eventLoop{eventLoop},
        logFilterView{logFilterView},
        logView{logView},
        logFileParser{logFileParser},
        textFilterWrapper{textFilterWrapper}
{
}

bool LogFilePresenter::Impl::checkLogLineFiltered(const LogLine& line)
{
    if(textFilterWrapper.passFilter(line.logLine))
    {
        if(line.level == LogLevel::Debug && logFilterView.getDebugChecked())
        {
            return true;
        }
        if(line.level == LogLevel::Info  && logFilterView.getInfoChecked())
        {
            return true;
        }
        if(line.level == LogLevel::Warning && logFilterView.getWarningChecked())
        {
            return true;
        }
        if(line.level == LogLevel::Error && logFilterView.getErrorChecked())
        {
            return true;
        }
        if(line.level == LogLevel::Unknown)
        {
            return true;
        }
    }
    return false;
}

void LogFilePresenter::Impl::updateLogData(
    const std::filesystem::path& filePath, 
    bool readLogFile, 
    LogDataModel& logDataModel)
{
    if(readLogFile)
    {
        eventLoop.post([&](){
            logFileParser.readLogFileData(filePath, logDataModel);
        });
    }

    if(logDataModel.getCompleted())
    {
        auto logData = logDataModel.getLogData();

        for(auto data : logData)
        {
            if(checkLogLineFiltered(data))
            {
                logView.drawLogLineText(data);
            }
        }
    }
}

LogFilePresenter::LogFilePresenter(
        WindowFactory& windowFactory,
        LogEventHandling::IEventLoop& eventLoop,
        LogFilterView& logFilterView, 
        LogView& logView,
        LogFileParser& logFileParser,
        ImGuiTextFilterWrapper& textFilterWrapper) : 
    p {std::make_unique<Impl>(windowFactory, eventLoop, logFilterView, logView, logFileParser, textFilterWrapper)}
{
}

LogFilePresenter::~LogFilePresenter() = default;

void LogFilePresenter::update(const std::filesystem::path& filePath, bool readLogFile, LogDataModel& logDataModel)
{
    auto logFilterWindow = p->windowFactory.createChildWindow(WindowDefs::LogFilterChildWindow, ImVec2{0, 0}, ImVec2{0, 0});
    p->logFilterView.drawFilterCheckBoxes();
    {
        auto logFileContentWindow = p->windowFactory.createChildWindow(WindowDefs::LogFileContentChildWindow, ImVec2{0, 0}, ImVec2{0, 0});
        p->updateLogData(filePath, readLogFile, logDataModel);
    }
}

}