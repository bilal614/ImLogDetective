
#ifndef IMLOGDETECTIVE_PRESENTERS_LOGDATAMODELFACTORYIMPL_H
#define IMLOGDETECTIVE_PRESENTERS_LOGDATAMODELFACTORYIMPL_H

#include "presenters/LogDataModelFactory.h"
#include <memory>

namespace ImLogDetective
{

class LogDataModelFactoryImpl : public LogDataModelFactory
{
public:
    std::unique_ptr<LogDataModel> createLogDataModel(const std::string& source) override;

};

}

#endif