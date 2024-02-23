#include "models/LogDataModel.h"
#include <memory>
#include <string_view>

namespace LogAnalyzerTool
{

struct LogDataModel::Impl
{

    Impl(const std::string& dataSource);
    ~Impl() = default;

    LogLevel getLogLevel(std::string_view dataLine);

    const std::string dataSource;
    std::vector<LogData> logData;
};


LogDataModel::Impl::Impl(const std::string& dataSource) :
    dataSource{dataSource}
{
}

LogLevel LogDataModel::Impl::getLogLevel(std::string_view dataLine)
{
    if(dataLine.find("DEBUG") != std::string_view::npos)
    {
        return LogLevel::Debug;
    }
    if(dataLine.find("INFO") != std::string_view::npos)
    {
        return LogLevel::Info;
    }
    if(dataLine.find("WARNING") != std::string_view::npos)
    {
        return LogLevel::Warning;
    }
    if(dataLine.find("ERROR") != std::string_view::npos)
    {
        return LogLevel::Error;
    }
    return LogLevel::Unknown;
}

LogDataModel::LogDataModel(const std::string& dataSource) :
    p{std::make_unique<Impl>(dataSource)}
{
}

LogDataModel::~LogDataModel() = default;

void LogDataModel::addLogData(std::string dataLine)
{
    p->logData.emplace_back(LogData{dataLine, p->getLogLevel(dataLine)});
}

const std::vector<LogData>& LogDataModel::getLogData()
{
    return p->logData;
}

}