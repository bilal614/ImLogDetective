#pragma once

#include "views/IFileListView.h"
#include <memory>

namespace LogAnalyzerTool
{

class FileListView : public IFileListView
{
public:
    FileListView();
    ~FileListView();
    void draw() override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}