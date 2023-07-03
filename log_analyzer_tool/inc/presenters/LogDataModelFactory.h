#pragma once

#include "presenters/ILogDataModelFactory.h"
#include <memory>

namespace LogAnalyzerTool
{

class LogDataModelFactory : public ILogDataModelFactory
{
public:
    std::unique_ptr<ILogDataModel> createLogDataModel(const std::string& source) override;

};

}