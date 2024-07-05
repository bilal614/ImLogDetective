
#ifndef IMLOGDETECTIVE_PRESENTERS_LOGDATAMODELFACTORY_H
#define IMLOGDETECTIVE_PRESENTERS_LOGDATAMODELFACTORY_H

#include <memory>
#include <string>

namespace ImLogDetective
{

class LogDataModel;

class LogDataModelFactory
{
public:
    virtual ~LogDataModelFactory() = default;
    virtual std::unique_ptr<LogDataModel> createLogDataModel(const std::string& source) = 0;
};

}

#endif