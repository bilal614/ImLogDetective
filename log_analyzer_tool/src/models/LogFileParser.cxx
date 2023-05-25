#include "models/LogFileParser.h"
#include "models/ILogDataModel.h"
#include <memory>
#include <fstream>
#include <sstream>

namespace LogAnalyzerTool
{

struct LogFileParser::Impl
{
    Impl();
    ~Impl() = default;
    struct ScopeFileStream{
        std::unique_ptr<std::ifstream> inputFile;

        ScopeFileStream(const std::filesystem::path& filePath) :
            inputFile{std::make_unique<std::ifstream>(filePath)}
        {
            if (!*inputFile) 
            {
                //report error
            }
        }

        ~ScopeFileStream()
        {
            inputFile->close();
        }
    };

};

LogFileParser::Impl::Impl()
{
}

LogFileParser::LogFileParser() :
    p{std::make_unique<Impl>()}
{
}

LogFileParser::~LogFileParser() = default;

void LogFileParser::readLogFileData(const std::filesystem::path& filePath, ILogDataModel& logDataModel)
{
    Impl::ScopeFileStream logFile{filePath};
    std::string line;
    while (std::getline(*logFile.inputFile, line))
    {
        if(line.size() > 0)
        {
            logDataModel.addLogData(line);
        }
    }
}


}