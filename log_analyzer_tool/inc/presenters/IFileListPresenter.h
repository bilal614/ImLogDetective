#pragma once

#include <filesystem>

namespace LogAnalyzerTool
{

class IFileListPresenter
{
public:
    virtual ~IFileListPresenter() = default;
    virtual void update(const std::filesystem::path& filePath) = 0;
};

}