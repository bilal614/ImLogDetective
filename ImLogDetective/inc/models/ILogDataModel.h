#pragma once

#include <string>
#include <vector>

namespace ImLogDetective
{

class ITextWidgetFactory;
struct LogLine;

class ILogDataModel 
{
public:
    virtual ~ILogDataModel() = default;
    virtual void addLogData(std::string dataLine) = 0;
    virtual const std::vector<LogLine>& getLogData() = 0; 
    virtual void setCompleted(bool completed) = 0;
    virtual bool getCompleted() = 0;
};

}