#pragma once

#include <filesystem>
#include <sstream>

namespace LogAnalyzerTool
{

class IGzipFile
{
public:
    virtual ~IGzipFile() = default;
    virtual std::stringstream decompress(const std::filesystem::path& filePath) = 0;
    virtual bool isGzipFormat(const std::filesystem::path& filePath) = 0;
};

}