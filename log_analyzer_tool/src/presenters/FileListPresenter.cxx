#include "presenters/FileListPresenter.h"
#include "views/IFileListView.h"
#include <memory>

namespace LogAnalyzerTool
{

struct FileListPresenter::Impl
{
    Impl(IFileListView& fileListView);
    ~Impl() = default;

    IFileListView& fileListView;
};

FileListPresenter::FileListPresenter(IFileListView& fileListView)
{
}

FileListPresenter::~FileListPresenter() = default;

void FileListPresenter::update(const std::filesystem::path& filePath)
{

}

}