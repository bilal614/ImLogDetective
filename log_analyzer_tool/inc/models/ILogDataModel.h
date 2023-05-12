#pragma once

#include <string_view>
#include <vector>

namespace LogAnalyzerTool
{

class ITextWidgetFactory;

class ILogDataModel 
{
public:
    virtual ~ILogDataModel() = default;
    virtual void addLogData(std::string_view dataLine) = 0;
    virtual void addMultipleLogData(const std::vector<std::string>&& data) = 0;
    virtual std::vector<std::string_view> getLogData() = 0; 
};

}