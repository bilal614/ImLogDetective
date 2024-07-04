#include "views/LogViewImpl.h"
#include "views/TextWidgetFactory.h"
#include "models/LogLine.h"

namespace ImLogDetective
{

struct LogViewImpl::Impl
{
    Impl(TextWidgetFactory& textWidgetFactory);
    ~Impl() = default;
    TextWidgetFactory& textWidgetFactory;
};

LogViewImpl::Impl::Impl(TextWidgetFactory& textWidgetFactory) :
    textWidgetFactory{textWidgetFactory}
{
}

LogViewImpl::LogViewImpl(TextWidgetFactory& textWidgetFactory) :
    p{std::make_unique<Impl>(textWidgetFactory)}
{
}

LogViewImpl::~LogViewImpl() = default;

void LogViewImpl::drawLogLineText(LogLine& logLine)
{
    logLine.selected = p->textWidgetFactory.createSelectedTextColored(
        logLine.logLine,
        logLine.color,
        logLine.selected);
}

}