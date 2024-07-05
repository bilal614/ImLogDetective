#pragma once

#include "presenters/LogDataModelFactory.h"
#include "gmock/gmock.h"
#include <string>
#include <vector>

namespace TestImLogDetective {

class LogDataModelFactoryMock : public ImLogDetective::LogDataModelFactory 
{
public:
    MOCK_METHOD(std::unique_ptr<ImLogDetective::LogDataModel>, createLogDataModel, (const std::string&));
};

}