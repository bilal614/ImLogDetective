#pragma once

#include "models/ILogFileParser.h"
#include "models/ILogDataModel.h"
#include "gmock/gmock.h"

namespace TestLogAnalyzerTool {

class LogFileParserMock : public LogAnalyzerTool::ILogFileParser 
{
public:
    MOCK_METHOD(void, readLogFileData, (const std::filesystem::path& filePath, LogAnalyzerTool::ILogDataModel& logDataModel));
};

}