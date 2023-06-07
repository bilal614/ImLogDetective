#pragma once

#include <filesystem>
#include <functional>
#include <unordered_map>

namespace LogAnalyzerTool
{

class IFileListView
{
public:
    virtual ~IFileListView() = default;
    virtual void draw(const std::unordered_map<std::string, std::filesystem::path>& fileList) = 0;
};

}