#pragma once

#include <string>
#include <tuple>
#include <vector>

namespace ImLogDetective
{

class ITextWidgetFactory;
struct LogData;

class ILogDataModel 
{
public:
    virtual ~ILogDataModel() = default;
    virtual void addLogData(std::string dataLine) = 0;
    virtual const std::vector<LogData>& getLogData() = 0; 
};

}