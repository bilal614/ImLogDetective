
#ifndef IMLOGDETECTIVE_VIEWS_FILELISTVIEWIMPL_H
#define IMLOGDETECTIVE_VIEWS_FILELISTVIEWIMPL_H

#include "views/FileListView.h"
#include <functional>
#include <memory>

namespace ImLogDetective
{

class ListTreeFactory;

class FileListViewImpl : public FileListView
{
public:
    FileListViewImpl(ListTreeFactory& listTreeFactory);
    ~FileListViewImpl();
    void draw(const std::vector<std::string>& fileList) override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}

#endif