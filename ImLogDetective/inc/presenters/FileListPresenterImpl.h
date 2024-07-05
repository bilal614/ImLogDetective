
#ifndef IMLOGDETECTIVE_PRESENTERS_FILELISTPRESENTERIMPL_H
#define IMLOGDETECTIVE_PRESENTERS_FILELISTPRESENTERIMPL_H

#include "presenters/FileListPresenter.h"
#include <memory>

namespace ImLogDetective
{

class FileListView;
class LogFileTabsPresenter;

class FileListPresenterImpl : public FileListPresenter
{
public:
    FileListPresenterImpl(LogFileTabsPresenter& fileTabsPresenter, FileListView& fileListView);
    ~FileListPresenterImpl();
    void update(const std::filesystem::path& folderPath, bool forced) override;
    std::vector<std::filesystem::path> getSelectedFiles() override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}

#endif