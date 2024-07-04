#include "views/FileListViewImpl.h"
#include "views/ListTreeFactory.h"
#include "dearimgui/IListTreeWidget.h"
#include "ImLogDetectiveDefs.h"
#include <memory>

namespace ImLogDetective
{

struct FileListViewImpl::Impl
{
    Impl(ListTreeFactory& listTreeFactory);
    ~Impl() = default;

    ListTreeFactory& listTreeFactory;
};

FileListViewImpl::Impl::Impl(ListTreeFactory& listTreeFactory) :
    listTreeFactory{listTreeFactory}
{

}

FileListViewImpl::FileListViewImpl(ListTreeFactory& listTreeFactory) :
    p{std::make_unique<Impl>(listTreeFactory)}
{

}

FileListViewImpl::~FileListViewImpl() = default;

void FileListViewImpl::draw(const std::vector<std::string>& fileList)
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