#pragma once

#include <filesystem>

namespace LogAnalyzerTool
{

class ILogDataModel;

class ILogFileParser 
{
public:
    virtual ~ILogFileParser() = default;
    virtual void readLogFileData(const std::filesystem::path& filePath, ILogDataModel& logDataModel) = 0;
};

}