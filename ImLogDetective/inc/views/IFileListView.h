#pragma once

#include <filesystem>
#include <functional>
#include <unordered_map>

namespace ImLogDetective
{

class IFileListView
{
public:
    virtual ~IFileListView() = default;
    virtual void draw(const std::vector<std::string>& fileList) = 0;
    std::function<void(const std::string&)> fileListCallback;
};

}