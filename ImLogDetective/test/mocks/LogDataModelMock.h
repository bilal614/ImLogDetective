#pragma once

#include "models/ILogDataModel.h"
#include "models/LogData.h"
#include "gmock/gmock.h"
#include <string>
#include <vector>

namespace TestImLogDetective {

class LogDataModelMock : public ImLogDetective::ILogDataModel 
{
public:
    MOCK_METHOD(void, addLogData, (std::string dataLine)); 
    MOCK_METHOD(const std::vector<ImLogDetective::LogData>&, getLogData, ());
    MOCK_METHOD(void, setCompleted, (bool completed));
    MOCK_METHOD(bool, getCompleted, ());
};

}