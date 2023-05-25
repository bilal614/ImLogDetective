#pragma once

#include <string_view>
#include <tuple>
#include <vector>

namespace LogAnalyzerTool
{

class ITextWidgetFactory;

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
    const std::string logLine;
    const LogLevel level;
};

class ILogDataModel 
{
public:
    virtual ~ILogDataModel() = default;
    virtual void addLogData(std::string dataLine) = 0;
    virtual const std::vector<LogData>& getLogData() = 0; 
};

}