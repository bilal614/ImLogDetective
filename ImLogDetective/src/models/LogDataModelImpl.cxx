#include "models/LogDataModelImpl.h"
#include "models/LogLine.h"

namespace ImLogDetective
{

struct LogDataModelImpl::Impl
{

    Impl(const std::string& dataSource);
    ~Impl() = default;

    LogLevel getLogLevel(std::string_view dataLine);

    const std::string dataSource;
    std::vector<LogLine> logData;
    bool completed;
};


LogDataModelImpl::Impl::Impl(const std::string& dataSource) :
    dataSource{dataSource},
    logData{},
    completed{false}
{
}

LogLevel LogDataModelImpl::Impl::getLogLevel(std::string_view dataLine)
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

LogDataModelImpl::LogDataModelImpl(const std::string& dataSource) :
    p{std::make_unique<Impl>(dataSource)}
{
}

LogDataModelImpl::~LogDataModelImpl() = default;

void LogDataModelImpl::addLogData(std::string dataLine)
{
    p->logData.emplace_back(LogLine{dataLine, p->getLogLevel(dataLine)});
}

const std::vector<LogLine>& LogDataModelImpl::getLogData()
{
    return p->logData;
}

void LogDataModelImpl::setCompleted(bool completed)
{
    p->completed = completed;
}

bool LogDataModelImpl::getCompleted()
{
    return p->completed;
}

}