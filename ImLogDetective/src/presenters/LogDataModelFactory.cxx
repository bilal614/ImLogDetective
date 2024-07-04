#include "presenters/LogDataModelFactory.h"
#include "models/LogDataModelImpl.h"
#include <memory>

namespace ImLogDetective
{

std::unique_ptr<LogDataModel> LogDataModelFactory::createLogDataModel(const std::string& source)
{
    return std::make_unique<LogDataModelImpl>(source);
}


}