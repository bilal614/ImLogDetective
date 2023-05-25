#pragma once

#include "models/ILogFileParser.h"
#include <memory>

namespace LogAnalyzerTool
{

class LogFileParser : public ILogFileParser
{
public:
    LogFileParser();
    ~LogFileParser();
    void readLogFileData(const std::filesystem::path& filePath, ILogDataModel& logDataModel) override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}