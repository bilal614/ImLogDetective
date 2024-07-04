
#ifndef IMLOGDETECTIVE_VIEWS_LOGVIEWIMPL_H
#define IMLOGDETECTIVE_VIEWS_LOGVIEWIMPL_H

#include "views/LogView.h"
#include <memory>

namespace ImLogDetective
{

class TextWidgetFactory;
struct LogLine;

class LogViewImpl : public LogView
{
public:
    LogViewImpl(TextWidgetFactory& textWidgetFactory);
    ~LogViewImpl();
    void drawLogLineText(LogLine& logLine) override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}

#endif