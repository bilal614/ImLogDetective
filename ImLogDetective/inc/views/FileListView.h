
#ifndef IMLOGDETECTIVE_VIEWS_FILELISTVIEW_H
#define IMLOGDETECTIVE_VIEWS_FILELISTVIEW_H

#include <filesystem>
#include <functional>
#include <unordered_map>

namespace ImLogDetective
{

class FileListView
{
public:
    virtual ~FileListView() = default;
    virtual void draw(const std::vector<std::string>& fileList) = 0;
    std::function<void(const std::string&)> fileListCallback;
};

}

#endif