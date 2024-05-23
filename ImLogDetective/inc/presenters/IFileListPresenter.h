#pragma once

#include <filesystem>
#include <vector>

namespace ImLogDetective
{

class IFileListPresenter
{
public:
    virtual ~IFileListPresenter() = default;
    virtual std::vector<std::filesystem::path> getSelectedFiles() = 0;
    virtual void update(const std::filesystem::path& filePath, bool forced) = 0;
};

}