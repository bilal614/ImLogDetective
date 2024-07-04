
#ifndef IMLOGDETECTIVE_MODELS_LOGFILEPARSERIMPL_H
#define IMLOGDETECTIVE_MODELS_LOGFILEPARSERIMPL_H


#include "models/LogFileParser.h"
#include <memory>

namespace ImLogDetective
{

class GzipFile;

class LogFileParserImpl : public LogFileParser
{
public:
    LogFileParserImpl(GzipFile& gzipFile);
    ~LogFileParserImpl();
    void readLogFileData(const std::filesystem::path& filePath, LogDataModel& logDataModel) override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}

#endif