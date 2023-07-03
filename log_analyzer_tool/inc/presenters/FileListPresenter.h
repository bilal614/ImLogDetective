#pragma once

#include "presenters/IFileListPresenter.h"
#include <memory>

namespace LogAnalyzerTool
{

class IFileListView;
class ILogFileTabsPresenter;

class FileListPresenter : public IFileListPresenter
{
public:
    FileListPresenter(ILogFileTabsPresenter& fileTabsPresenter,IFileListView& fileListView);
    ~FileListPresenter();
    void update(const std::filesystem::path& folderPath) override;
    std::vector<std::filesystem::path> getSelectedFiles() override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}