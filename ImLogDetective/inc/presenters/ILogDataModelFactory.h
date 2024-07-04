#pragma once

#include <memory>
#include <string>

namespace ImLogDetective
{

class LogDataModel;

class ILogDataModelFactory
{
public:
    virtual ~ILogDataModelFactory() = default;
    virtual std::unique_ptr<LogDataModel> createLogDataModel(const std::string& source) = 0;
};

}