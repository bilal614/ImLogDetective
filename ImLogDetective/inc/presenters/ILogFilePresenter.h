#pragma once

#include <filesystem>

namespace ImLogDetective
{

class LogDataModel;
class ILogFilePresenter
{
public:
    virtual ~ILogFilePresenter() = default;
    virtual void update(const std::filesystem::path& filePath, bool readLogFile, LogDataModel& logDataModel) = 0;
};

}