#include "models/LogDataModel.h"
#include "models/LogLine.h"

namespace ImLogDetective
{

struct LogDataModel::Impl
{

    Impl(const std::string& dataSource);
    ~Impl() = default;

    LogLevel getLogLevel(std::string_view dataLine);

    const std::string dataSource;
    std::vector<LogLine> logData;
    bool completed;
};


LogDataModel::Impl::Impl(const std::string& dataSource) :
    dataSource{dataSource},
    logData{},
    completed{false}
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
    p->logData.emplace_back(LogLine{dataLine, p->getLogLevel(dataLine)});
}

const std::vector<LogLine>& LogDataModel::getLogData()
{
    return p->logData;
}

void LogDataModel::setCompleted(bool completed)
{
    p->completed = completed;
}

bool LogDataModel::getCompleted()
{
    return p->completed;
}

}