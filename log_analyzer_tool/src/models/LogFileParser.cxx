#include "models/LogFileParser.h"
#include "models/ILogDataModel.h"
#include "models/IGzipFile.h"
#include <memory>
#include <fstream>
#include <sstream>

namespace LogAnalyzerTool
{

struct LogFileParser::Impl
{
    Impl(IGzipFile& gzipFile);
    ~Impl() = default;
    std::unique_ptr<std::basic_istream<char>> getFileStream(const std::filesystem::path& filePath);

    IGzipFile& gzipFile;
};

LogFileParser::Impl::Impl(IGzipFile& gzipFile) :
    gzipFile{gzipFile}
{
}

std::unique_ptr<std::basic_istream<char>> LogFileParser::Impl::getFileStream(const std::filesystem::path& filePath)
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

LogFileParser::LogFileParser(IGzipFile& gzipFile) :
    p{std::make_unique<Impl>(gzipFile)}
{
}

LogFileParser::~LogFileParser() = default;

void LogFileParser::readLogFileData(const std::filesystem::path& filePath, ILogDataModel& logDataModel)
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
}

}