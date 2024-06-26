#include "views/LogView.h"
#include "views/ITextWidgetFactory.h"
#include "models/LogLine.h"

namespace ImLogDetective
{

struct LogView::Impl
{
    Impl(ITextWidgetFactory& textWidgetFactory);
    ~Impl() = default;
    ITextWidgetFactory& textWidgetFactory;
};

LogView::Impl::Impl(ITextWidgetFactory& textWidgetFactory) :
    textWidgetFactory{textWidgetFactory}
{
}

LogView::LogView(ITextWidgetFactory& textWidgetFactory) :
    p{std::make_unique<Impl>(textWidgetFactory)}
{
}

LogView::~LogView() = default;

void LogView::drawLogLineText(LogLine& logLine)
{
    logLine.selected = p->textWidgetFactory.createSelectedTextColored(
        logLine.logLine,
        logLine.color,
        logLine.selected);
}

}