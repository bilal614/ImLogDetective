#include "models/LogFileParserImpl.h"
#include "models/LogDataModel.h"
#include "models/GzipFile.h"
#include <memory>
#include <fstream>
#include <sstream>

namespace ImLogDetective
{

struct LogFileParserImpl::Impl
{
    Impl(GzipFile& gzipFile);
    ~Impl() = default;
    std::unique_ptr<std::basic_istream<char>> getFileStream(const std::filesystem::path& filePath);

    GzipFile& gzipFile;
};

LogFileParserImpl::Impl::Impl(GzipFile& gzipFile) :
    gzipFile{gzipFile}
{
}

std::unique_ptr<std::basic_istream<char>> LogFileParserImpl::Impl::getFileStream(const std::filesystem::path& filePath)
{
    std::unique_ptr<std::basic_istream<char>> logStream;
    if(gzipFile.isGzipFormat(filePath))
    {
        logStream = std::make_unique<std::stringstream>(gzipFile.decompress(filePath));
    }
    else
    {
        logStream = std::make_unique<std::fstream>(filePath);
    }
    return logStream;
}

LogFileParserImpl::LogFileParserImpl(GzipFile& gzipFile) :
    p{std::make_unique<Impl>(gzipFile)}
{
}

LogFileParserImpl::~LogFileParserImpl() = default;

void LogFileParserImpl::readLogFileData(const std::filesystem::path& filePath, LogDataModel& logDataModel)
{
    auto logFileStream = p->getFileStream(filePath);
    std::string line;
    while (std::getline(*logFileStream, line))
    {
        if(line.size() > 0)
        {
            logDataModel.addLogData(line);
        }
    }
    logDataModel.setCompleted(true);
}

}