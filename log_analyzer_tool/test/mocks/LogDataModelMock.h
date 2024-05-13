#pragma once

#include "models/ILogDataModel.h"
#include "gmock/gmock.h"
#include <string>
#include <vector>

namespace TestImLogDetective {

class LogDataModelMock : public ImLogDetective::ILogDataModel 
{
public:
    MOCK_METHOD(void, addLogData, (std::string dataLine)); 
    MOCK_METHOD(const std::vector<ImLogDetective::LogData>&, getLogData, ());
};

}