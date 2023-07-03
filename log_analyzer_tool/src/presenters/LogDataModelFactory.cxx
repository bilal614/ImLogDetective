#include "presenters/LogDataModelFactory.h"
#include "models/LogDataModel.h"
#include <memory>

namespace LogAnalyzerTool
{

std::unique_ptr<ILogDataModel> LogDataModelFactory::createLogDataModel(const std::string& source)
{
    return std::make_unique<LogDataModel>(source);
}


}