#pragma once

#include "models/LogFileParser.h"
#include "models/LogDataModel.h"
#include "gmock/gmock.h"

namespace TestImLogDetective {

class LogFileParserMock : public ImLogDetective::LogFileParser 
{
public:
    MOCK_METHOD(void, readLogFileData, (const std::filesystem::path& filePath, ImLogDetective::LogDataModel& logDataModel));
};

}