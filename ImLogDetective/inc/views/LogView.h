#pragma once

#include "views/ILogView.h"
#include <memory>
#include <string_view>

namespace ImLogDetective
{

class ITextWidgetFactory;
struct LogData;

class LogView : public ILogView
{
public:
    LogView(ITextWidgetFactory& textWidgetFactory);
    ~LogView();
    void drawLogLineText(LogData& logLine, const TextColor& color) override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}