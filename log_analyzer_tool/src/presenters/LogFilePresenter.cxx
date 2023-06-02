#include "LogAnalyzerToolDefs.h"
#include "presenters/LogFilePresenter.h"
#include "views/ILogView.h"
#include "views/ILogFilterView.h"
#include "dearimgui/IImGuiTextFilterWrapper.h"
#include "dearimgui/ITextWidgetFactory.h"
#include "dearimgui/IWindowFactory.h"
#include "models/ILogFileParser.h"
#include "models/ILogDataModel.h"

namespace LogAnalyzerTool
{

struct LogFilePresenter::Impl
{
    Impl(IWindowFactory& windowFactory,
        ILogFilterView& logFilterView, 
        ILogView& logView,
        ILogFileParser& logFileParser,
        IImGuiTextFilterWrapper& textFilterWrapper);
    ~Impl() = default;

    IWindowFactory& windowFactory;
    ILogFilterView& logFilterView;
    ILogView& logView;
    ILogFileParser& logFileParser;
    IImGuiTextFilterWrapper& textFilterWrapper;
};

LogFilePresenter::Impl::Impl(IWindowFactory& windowFactory,
        ILogFilterView& logFilterView, 
        ILogView& logView,
        ILogFileParser& logFileParser,
        IImGuiTextFilterWrapper& textFilterWrapper) :
    windowFactory{windowFactory},
    logFilterView{logFilterView},
    logView{logView},
    logFileParser{logFileParser},
    textFilterWrapper{textFilterWrapper}
{
}

LogFilePresenter::LogFilePresenter(
        IWindowFactory& windowFactory,
        ILogFilterView& logFilterView, 
        ILogView& logView,
        ILogFileParser& logFileParser,
        IImGuiTextFilterWrapper& textFilterWrapper) : 
    p {std::make_unique<Impl>(windowFactory, logFilterView, logView, logFileParser, textFilterWrapper)}
{
}

LogFilePresenter::~LogFilePresenter() = default;

void LogFilePresenter::update(const std::filesystem::path& filePath, bool readLogFile, ILogDataModel& logDataModel)
{
    //TODO Below must move to ILogFilePresenter
    auto logFilterWindow = p->windowFactory.createChildWindow(LogFilterChildWindow);
    p->logFilterView.drawFilterCheckBoxes();
    {
        auto logFileContentWindow = p->windowFactory.createChildWindow(LogFileContentChildWindow);
        if(readLogFile)
        {
            p->logFileParser.readLogFileData(filePath, logDataModel);
        }
        auto logData = logDataModel.getLogData();

        for(auto data : logData)
        {
            if(p->textFilterWrapper.passFilter(data.logLine))
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

}