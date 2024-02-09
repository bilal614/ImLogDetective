#include "views/FileListView.h"
#include "views/IListTreeFactory.h"
#include "dearimgui/IListTreeWidget.h"
#include "LogAnalyzerToolDefs.h"
#include <memory>

namespace LogAnalyzerTool
{

struct FileListView::Impl
{
    Impl(IListTreeFactory& listTreeFactory);
    ~Impl() = default;

    IListTreeFactory& listTreeFactory;
};

FileListView::Impl::Impl(IListTreeFactory& listTreeFactory) :
    listTreeFactory{listTreeFactory}
{

}

FileListView::FileListView(IListTreeFactory& listTreeFactory) :
    p{std::make_unique<Impl>(listTreeFactory)}
{

}

FileListView::~FileListView() = default;

void FileListView::draw(const std::vector<std::string>& fileList)
{
    if(!fileList.empty())
    {
        auto listTree = p->listTreeFactory.createListTreeWidget();
        for(auto& fileItem : fileList)
        {
            listTree->addNode(fileItem, [&](){fileListCallback(fileItem);});
        }
    }
}

}