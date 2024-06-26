#pragma once

#include "models/ILogDataModel.h"
#include <memory>
#include <vector>

namespace ImLogDetective
{

class ITextWidgetFactory;

class LogDataModel : public ILogDataModel
{
public:
    LogDataModel(const std::string& dataSource);
    ~LogDataModel();
    void addLogData(std::string dataLine) override;
    const std::vector<LogLine>& getLogData() override; 
    void setCompleted(bool completed) override;
    bool getCompleted() override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}