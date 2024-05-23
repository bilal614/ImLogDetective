#pragma once

#include <filesystem>

namespace ImLogDetective
{

class ILogDataModel;
class ILogFilePresenter
{
public:
    virtual ~ILogFilePresenter() = default;
    virtual void update(const std::filesystem::path& filePath, bool readLogFile, ILogDataModel& logDataModel) = 0;
};

}