#pragma once

#include "presenters/IFileListPresenter.h"
#include <memory>

namespace LogAnalyzerTool
{

class IFileListView;

class FileListPresenter : public IFileListPresenter
{
public:
    FileListPresenter(IFileListView& fileListView);
    ~FileListPresenter();
    void update(const std::filesystem::path& folderPath) override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}