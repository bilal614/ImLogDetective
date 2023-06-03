#include "views/FileListView.h"
#include <memory>

namespace LogAnalyzerTool
{

struct FileListView::Impl
{
    Impl();
    ~Impl() = default;
};

FileListView::Impl::Impl()
{

}

FileListView::FileListView() :
    p{std::make_unique<Impl>()}
{

}

FileListView::~FileListView() = default;
void FileListView::draw()
{

}

}