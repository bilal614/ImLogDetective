#include "presenters/LogDataModelFactoryImpl.h"
#include "models/LogDataModelImpl.h"
#include <memory>

namespace ImLogDetective
{

std::unique_ptr<LogDataModel> LogDataModelFactoryImpl::createLogDataModel(const std::string& source)
{
    return std::make_unique<LogDataModelImpl>(source);
}


}