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
    void addLogData(std::string_view dataLine) override;
    void addMultipleLogData(const std::vector<std::string>&& data) override;
    std::vector<std::string_view> getLogData() override; 
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}