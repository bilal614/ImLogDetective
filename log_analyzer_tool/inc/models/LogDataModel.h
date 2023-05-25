#pragma once

#include "models/ILogDataModel.h"
#include <memory>

namespace LogAnalyzerTool
{

class ITextWidgetFactory;

class LogDataModel : public ILogDataModel
{
public:
    LogDataModel(const std::string& dataSource);
    ~LogDataModel();
    void addLogData(std::string dataLine) override;
    const std::vector<LogData>& getLogData() override; 
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}