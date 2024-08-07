#pragma once

#include "models/LogDataModel.h"
#include "models/LogLine.h"
#include <gmock/gmock.h>
#include <string>
#include <vector>

namespace TestImLogDetective {

class LogDataModelMock : public ImLogDetective::LogDataModel 
{
public:
    MOCK_METHOD(void, addLogData, (std::string dataLine)); 
    MOCK_METHOD(const std::vector<ImLogDetective::LogLine>&, getLogData, ());
    MOCK_METHOD(void, setCompleted, (bool completed));
    MOCK_METHOD(bool, getCompleted, ());
};

}