#include "views/LogView.h"
#include "dearimgui/ITextWidgetFactory.h"

namespace LogAnalyzerTool
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

void LogView::drawLogLineText(std::string_view logText, const TextColor& color)
{
    p->textWidgetFactory.createTextColored(logText, color);
}

}