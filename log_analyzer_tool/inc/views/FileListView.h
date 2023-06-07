#pragma once

#include "views/IFileListView.h"
#include <memory>

namespace LogAnalyzerTool
{

class IListTreeFactory;

class FileListView : public IFileListView
{
public:
    FileListView(IListTreeFactory& listTreeFactory);
    ~FileListView();
    void draw(const std::unordered_map<std::string, std::filesystem::path>& fileList) override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}