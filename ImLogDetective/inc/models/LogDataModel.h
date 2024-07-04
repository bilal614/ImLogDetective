
#ifndef IMLOGDETECTIVE_MODELS_LOGDATAMODEL_H
#define IMLOGDETECTIVE_MODELS_LOGDATAMODEL_H

#include <string>
#include <vector>

namespace ImLogDetective
{

struct LogLine;

class LogDataModel 
{
public:
    virtual ~LogDataModel() = default;
    virtual void addLogData(std::string dataLine) = 0;
    virtual const std::vector<LogLine>& getLogData() = 0; 
    virtual void setCompleted(bool completed) = 0;
    virtual bool getCompleted() = 0;
};

}

#endif