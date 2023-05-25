#pragma once

#include <filesystem>

namespace LogAnalyzerTool
{

class ILogFilePresenter
{
public:
    virtual ~ILogFilePresenter() = default;
    virtual void update(const std::filesystem::path& filePath) = 0;
};

}