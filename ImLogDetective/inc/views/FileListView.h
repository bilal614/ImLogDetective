#pragma once

#include "views/IFileListView.h"
#include <functional>
#include <memory>

namespace ImLogDetective
{

class IListTreeFactory;

class FileListView : public IFileListView
{
public:
    FileListView(IListTreeFactory& listTreeFactory);
    ~FileListView();
    void draw(const std::vector<std::string>& fileList) override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}