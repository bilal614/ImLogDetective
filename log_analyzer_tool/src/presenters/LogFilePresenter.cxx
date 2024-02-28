#include "LogAnalyzerToolDefs.h"
#include "dearimgui/IImGuiTextFilterWrapper.h"
#include "views/ITextWidgetFactory.h"
#include "views/IWindowFactory.h"
#include "models/ILogFileParser.h"
#include "event_handling/Event.hpp"
#include "event_handling/IEventLoop.h"
#include "models/ILogDataModel.h"
#include "presenters/LogFilePresenter.h"
#include "views/ILogView.h"
#include "views/ILogFilterView.h"
#include "imgui.h"

namespace LogAnalyzerTool
{

struct LogFilePresenter::Impl
{
    Impl(IWindowFactory& windowFactory,
        IEventLoop& eventLoop,
        ILogFilterView& logFilterView, 
        ILogView& logView,
        ILogFileParser& logFileParser,
        IImGuiTextFilterWrapper& textFilterWrapper);
    ~Impl() = default;
    void updateLogData(const std::filesystem::path& filePath, bool readLogFile, ILogDataModel& logDataModel);

    IWindowFactory& windowFactory;
    IEventLoop& eventLoop;
    ILogFilterView& logFilterView;
    ILogView& logView;
    ILogFileParser& logFileParser;
    IImGuiTextFilterWrapper& textFilterWrapper;
};

LogFilePresenter::Impl::Impl(
    IWindowFactory& windowFactory,
    IEventLoop& eventLoop,
    ILogFilterView& logFilterView, 
    ILogView& logView,
    ILogFileParser& logFileParser,
    IImGuiTextFilterWrapper& textFilterWrapper) :
        windowFactory{windowFactory},
        eventLoop{eventLoop},
        logFilterView{logFilterView},
        logView{logView},
        logFileParser{logFileParser},
        textFilterWrapper{textFilterWrapper}
{
}

void LogFilePresenter::Impl::updateLogData(
    const std::filesystem::path& filePath, 
    bool readLogFile, 
    ILogDataModel& logDataModel)
{
    if(readLogFile)
    {
        eventLoop.post([&](){
            logFileParser.readLogFileData(filePath, logDataModel);
        });
    }

    auto logData = logDataModel.getLogData();

    for(auto data : logData)
    {
        if(textFilterWrapper.passFilter(data.logLine))
        {
            if(data.level == LogLevel::Unknown)
            {
                logView.drawLogLineText(data.logLine, TextColor::Yellow);
            }
            if(data.level == LogLevel::Debug && logFilterView.getDebugChecked())
            {
                logView.drawLogLineText(data.logLine, TextColor::White);
            }
            if(data.level == LogLevel::Info  && logFilterView.getInfoChecked())
            {
                logView.drawLogLineText(data.logLine, TextColor::White);
            }
            if(data.level == LogLevel::Warning && logFilterView.getWarningChecked())
            {
                logView.drawLogLineText(data.logLine, TextColor::Orange);
            }
            if(data.level == LogLevel::Error && logFilterView.getErrorChecked())
            {
                logView.drawLogLineText(data.logLine, TextColor::Red);
            }
        }
    }
}

LogFilePresenter::LogFilePresenter(
        IWindowFactory& windowFactory,
        IEventLoop& eventLoop,
        ILogFilterView& logFilterView, 
        ILogView& logView,
        ILogFileParser& logFileParser,
        IImGuiTextFilterWrapper& textFilterWrapper) : 
    p {std::make_unique<Impl>(windowFactory, eventLoop, logFilterView, logView, logFileParser, textFilterWrapper)}
{
}

LogFilePresenter::~LogFilePresenter() = default;

void LogFilePresenter::update(const std::filesystem::path& filePath, bool readLogFile, ILogDataModel& logDataModel)
{
    auto logFilterWindow = p->windowFactory.createChildWindow(WindowDefs::LogFilterChildWindow, ImVec2{0, 0}, ImVec2{0, 0});
    p->logFilterView.drawFilterCheckBoxes();
    {
        auto logFileContentWindow = p->windowFactory.createChildWindow(WindowDefs::LogFileContentChildWindow, ImVec2{0, 0}, ImVec2{0, 0});
        p->updateLogData(filePath, readLogFile, logDataModel);
    }
}

}