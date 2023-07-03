#pragma once

#include <filesystem>
#include <vector>

namespace LogAnalyzerTool
{

class IFileListPresenter
{
public:
    virtual ~IFileListPresenter() = default;
    virtual std::vector<std::filesystem::path> getSelectedFiles() = 0;
    virtual void update(const std::filesystem::path& filePath) = 0;
};

}