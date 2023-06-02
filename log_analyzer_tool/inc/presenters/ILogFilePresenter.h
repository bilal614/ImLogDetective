#pragma once

#include <filesystem>

namespace LogAnalyzerTool
{

class ILogDataModel;
class ILogFilePresenter
{
public:
    virtual ~ILogFilePresenter() = default;
    virtual void update(const std::filesystem::path& filePath, bool readLogFile, ILogDataModel& logDataModel) = 0;
};

}