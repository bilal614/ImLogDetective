#pragma once

#include <filesystem>

namespace LogAnalyzerTool
{

class ILogFileTabsPresenter
{
public:
    virtual ~ILogFileTabsPresenter() = default;
    virtual void update(const std::filesystem::path& folderPath) = 0;
};

}