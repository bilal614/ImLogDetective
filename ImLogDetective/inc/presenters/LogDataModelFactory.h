#pragma once

#include "presenters/ILogDataModelFactory.h"
#include <memory>

namespace ImLogDetective
{

class LogDataModelFactory : public ILogDataModelFactory
{
public:
    std::unique_ptr<LogDataModel> createLogDataModel(const std::string& source) override;

};

}