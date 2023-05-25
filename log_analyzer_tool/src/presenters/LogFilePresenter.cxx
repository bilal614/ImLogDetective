#include "presenters/LogFilePresenter.h"
#include "views/ILogView.h"
#include "views/ILogFilterView.h"
#include "dearimgui/ITextWidgetFactory.h"
#include "dearimgui/IWindowFactory.h"
#include "dearimgui/ScopedImGuiWindow.hpp"
#include "models/ILogFileParser.h"

//TODO Remove later
#include "models/LogDataModel.h"


namespace LogAnalyzerTool
{

struct LogFilePresenter::Impl
{
    Impl(IWindowFactory& windowFactory,
        ILogFilterView& logFilterView, 
        ILogView& logView,
        ILogFileParser& logFileParser);
    ~Impl() = default;

    bool logDataIsRead;
    IWindowFactory& windowFactory;
    ILogFilterView& logFilterView;
    ILogView& logView;
    ILogFileParser& logFileParser;
    
    //TODO Remove later
    LogDataModel logDataModel;
};

LogFilePresenter::Impl::Impl(IWindowFactory& windowFactory,
        ILogFilterView& logFilterView, 
        ILogView& logView,
        ILogFileParser& logFileParser) :
    windowFactory{windowFactory},
    logFilterView{logFilterView},
    logView{logView},
    logFileParser{logFileParser},
    logDataModel{"Dummy Data"},
    logDataIsRead{false}
{
}

LogFilePresenter::LogFilePresenter(
        IWindowFactory& windowFactory,
        ILogFilterView& logFilterView, 
        ILogView& logView,
        ILogFileParser& logFileParser) : 
    p {std::make_unique<Impl>(windowFactory, logFilterView, logView, logFileParser)}
{
}

LogFilePresenter::~LogFilePresenter() = default;

void LogFilePresenter::update(const std::filesystem::path& filePath)
{
    //TODO Below must move to ILogFilePresenter
    auto logFilterWindow = p->windowFactory.createChildWindow("LogFilterWindow");
    p->logFilterView.drawFilterCheckBoxes();
    {
        auto logFileContentWindow = p->windowFactory.createChildWindow("LogFileContentWindow");
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