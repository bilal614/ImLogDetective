
#ifndef IMLOGDETECTIVE_MODELS_LOGLINE_H
#define IMLOGDETECTIVE_MODELS_LOGLINE_H

#include "dearimgui/TextColor.h"
#include <string>

namespace ImLogDetective
{

enum LogLevel 
{
    Debug,
    Info, 
    Warning,
    Error,
    Unknown
};

struct LogLine
{
    LogLine();
    LogLine(const std::string line, LogLevel level);
    bool operator==(const LogLine& data) const;

    const std::string logLine;
    const LogLevel level;
    const TextColor color;
    bool selected;
};

}

#endif