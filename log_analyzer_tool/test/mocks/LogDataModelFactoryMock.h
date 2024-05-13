#pragma once

#include "presenters/ILogDataModelFactory.h"
#include "gmock/gmock.h"
#include <string>
#include <vector>

namespace TestImLogDetective {

class LogDataModelFactoryMock : public ImLogDetective::ILogDataModelFactory 
{
public:
    MOCK_METHOD(std::unique_ptr<ImLogDetective::ILogDataModel>, createLogDataModel, (const std::string&));
};

}