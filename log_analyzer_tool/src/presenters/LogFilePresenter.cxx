#include "LogAnalyzerToolDefs.h"
#include "presenters/LogFilePresenter.h"
#include "views/ILogView.h"
#include "views/ILogFilterView.h"
#include "dearimgui/ITextWidgetFactory.h"
#include "dearimgui/IWindowFactory.h"
#include "models/ILogFileParser.h"
#include "models/ILogDataModel.h"

//TODO Remove later


namespace LogAnalyzerTool
{

struct LogFilePresenter::Impl
{
    Impl(IWindowFactory& windowFactory,
        ILogFilterView& logFilterView, 
        ILogView& logView,
        ILogFileParser& logFileParser,
        ILogDataModel& logDataModel);
    ~Impl() = default;

    bool logDataIsRead;
    IWindowFactory& windowFactory;
    ILogFilterView& logFilterView;
    ILogView& logView;
    ILogFileParser& logFileParser;
    ILogDataModel& logDataModel;
};

LogFilePresenter::Impl::Impl(IWindowFactory& windowFactory,
        ILogFilterView& logFilterView, 
        ILogView& logView,
        ILogFileParser& logFileParser,
        ILogDataModel& logDataModel) :
    windowFactory{windowFactory},
    logFilterView{logFilterView},
    logView{logView},
    logFileParser{logFileParser},
    logDataModel{logDataModel},
    logDataIsRead{false}
{
}

LogFilePresenter::LogFilePresenter(
        IWindowFactory& windowFactory,
        ILogFilterView& logFilterView, 
        ILogView& logView,
        ILogFileParser& logFileParser,
        ILogDataModel& logDataModel) : 
    p {std::make_unique<Impl>(windowFactory, logFilterView, logView, logFileParser, logDataModel)}
{
}

LogFilePresenter::~LogFilePresenter() = default;

void LogFilePresenter::update(const std::filesystem::path& filePath)
{
    //TODO Below must move to ILogFilePresenter
    auto logFilterWindow = p->windowFactory.createChildWindow(LogFilterChildWindow);
    p->logFilterView.drawFilterCheckBoxes();
    {
        auto logFileContentWindow = p->windowFactory.createChildWindow(LogFileContentChildWindow);
        if(!p->logDataIsRead)
        {
            p->logDataIsRead = true;
            p->logFileParser.readLogFileData(filePath, p->logDataModel);
        }
        auto logData = p->logDataModel.getLogData(); 
        for(auto data : logData)
        {
            if(data.level == LogLevel::Debug && p->logFilterView.getDebugChecked())
            {
                p->logView.drawLogLineText(data.logLine, TextColor::White);
            }
            if(data.level == LogLevel::Info  && p->logFilterView.getInfoChecked())
            {
                p->logView.drawLogLineText(data.logLine, TextColor::White);
            }
            if(data.level == LogLevel::Warning && p->logFilterView.getWarningChecked())
            {
                p->logView.drawLogLineText(data.logLine, TextColor::Orange);
            }
            if(data.level == LogLevel::Error && p->logFilterView.getErrorChecked())
            {
                p->logView.drawLogLineText(data.logLine, TextColor::Red);
            }
        }
    }
}

}