#pragma once

#include <string>
#include <tuple>
#include <vector>

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

struct LogData
{
    LogData() :
        LogData{std::string{}, LogLevel::Unknown}
    {
    }
    LogData(const std::string line, LogLevel level) :
        logLine{line},
        level{level},
        selected{false}
    {
    }
    const std::string logLine;
    const LogLevel level;
    bool selected;

    bool operator==(const LogData& data) const
    {
        return data.logLine == logLine && data.level == level && data.selected == selected;
    }
};

}