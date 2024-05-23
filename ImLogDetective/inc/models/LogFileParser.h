#pragma once

#include "models/ILogFileParser.h"
#include <memory>

namespace ImLogDetective
{

class IGzipFile;

class LogFileParser : public ILogFileParser
{
public:
    LogFileParser(IGzipFile& gzipFile);
    ~LogFileParser();
    void readLogFileData(const std::filesystem::path& filePath, ILogDataModel& logDataModel) override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}