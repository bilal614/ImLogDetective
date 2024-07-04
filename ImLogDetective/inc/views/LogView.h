
#ifndef IMLOGDETECTIVE_VIEWS_LOGVIEW_H
#define IMLOGDETECTIVE_VIEWS_LOGVIEW_H

#include <string_view>

namespace ImLogDetective
{

struct LogLine;
enum class TextColor;

class LogView
{
public:
    virtual ~LogView() = default;
    virtual void drawLogLineText(LogLine& logLine) = 0;
};

}

#endif