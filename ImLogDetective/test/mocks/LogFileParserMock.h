#pragma once

#include "models/ILogFileParser.h"
#include "models/ILogDataModel.h"
#include "gmock/gmock.h"

namespace TestImLogDetective {

class LogFileParserMock : public ImLogDetective::ILogFileParser 
{
public:
    MOCK_METHOD(void, readLogFileData, (const std::filesystem::path& filePath, ImLogDetective::ILogDataModel& logDataModel));
};

}