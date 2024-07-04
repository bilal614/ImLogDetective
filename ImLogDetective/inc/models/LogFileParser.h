
#ifndef IMLOGDETECTIVE_MODELS_LOGFILEPARSER_H
#define IMLOGDETECTIVE_MODELS_LOGFILEPARSER_H

#include <filesystem>

namespace ImLogDetective
{

class LogDataModel;

class LogFileParser 
{
public:
    virtual ~LogFileParser() = default;
    virtual void readLogFileData(const std::filesystem::path& filePath, LogDataModel& logDataModel) = 0;
};

}

#endif