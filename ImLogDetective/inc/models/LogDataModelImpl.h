
#ifndef IMLOGDETECTIVE_MODELS_LOGDATAMODELIMPL_H
#define IMLOGDETECTIVE_MODELS_LOGDATAMODELIMPL_H

#include "models/LogDataModel.h"
#include <memory>
#include <vector>

namespace ImLogDetective
{

class ITextWidgetFactory;

class LogDataModelImpl : public LogDataModel
{
public:
    LogDataModelImpl(const std::string& dataSource);
    ~LogDataModelImpl();
    void addLogData(std::string dataLine) override;
    const std::vector<LogLine>& getLogData() override;
    void setCompleted(bool completed) override;
    bool getCompleted() override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}

#endif