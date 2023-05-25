#include "presenters/LogFilePresenterFactory.h"
#include "presenters/LogFilePresenter.h"
#include <memory>

namespace LogAnalyzerTool
{

class ILogFileParser;
class ILogFilterView;
class ILogView;
class IWindowFactory;
struct LogFilePresenterFactory::Impl
{
    Impl(IWindowFactory& windowFactory,
        ILogFilterView& logFilterView, 
        ILogView& logView,
        ILogFileParser& logFileParser);
    ~Impl() = default;

    IWindowFactory& windowFactory;
    ILogFilterView& logFilterView; 
    ILogView& logView;
    ILogFileParser& logFileParser;
};

LogFilePresenterFactory::Impl::Impl(IWindowFactory& windowFactory,
        ILogFilterView& logFilterView, 
        ILogView& logView,
        ILogFileParser& logFileParser) :
    windowFactory{windowFactory},
    logFilterView{logFilterView},
    logView{logView},
    logFileParser{logFileParser}
{

}

LogFilePresenterFactory::LogFilePresenterFactory(IWindowFactory& windowFactory,
        ILogFilterView& logFilterView, 
        ILogView& logView,
        ILogFileParser& logFileParser) :
    p{std::make_unique<Impl>(windowFactory, logFilterView, logView, logFileParser)}
{
}

LogFilePresenterFactory::~LogFilePresenterFactory() = default;

std::unique_ptr<ILogFilePresenter> LogFilePresenterFactory::createLogFilePresenter(const std::filesystem::path& filePath)
{
    return std::make_unique<LogFilePresenter>(p->windowFactory, p->logFilterView, p->logView, p->logFileParser);
}

}