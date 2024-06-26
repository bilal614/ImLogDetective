#pragma once

#include "views/ILogView.h"
#include <memory>

namespace ImLogDetective
{

class ITextWidgetFactory;
struct LogLine;

class LogView : public ILogView
{
public:
    LogView(ITextWidgetFactory& textWidgetFactory);
    ~LogView();
    void drawLogLineText(LogLine& logLine) override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}