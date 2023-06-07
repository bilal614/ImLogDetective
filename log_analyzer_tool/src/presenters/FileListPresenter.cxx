#include "presenters/FileListPresenter.h"
#include "views/IFileListView.h"
#include <memory>

//REMOVE LATER
#include <iostream>

namespace LogAnalyzerTool
{

struct FileListPresenter::Impl
{
    Impl(IFileListView& fileListView);
    ~Impl() = default;

    IFileListView& fileListView;
    std::filesystem::path folderPath;

    std::unordered_map<std::string, std::filesystem::path> fileList;

    std::function<void()> fileListClickCallback; 
};

FileListPresenter::Impl::Impl(IFileListView& fileListView) :
    fileListView{fileListView},
    folderPath{},
    fileListClickCallback{[&]{ std::cout << "Clicked" << std::endl;}}
{

}


FileListPresenter::FileListPresenter(IFileListView& fileListView) :
    p{std::make_unique<Impl>(fileListView)}
{
}

FileListPresenter::~FileListPresenter() = default;

void FileListPresenter::update(const std::filesystem::path& folderPath)
{
    bool folderPathChanged = false;
    if(p->folderPath != folderPath)
    {
        folderPathChanged = true;
        p->folderPath = folderPath;
        
        for (const auto& entry : std::filesystem::directory_iterator(p->folderPath))
        {
            if(entry.is_regular_file())
            {
                auto tabName = entry.path().stem();
                p->fileList.insert({tabName, entry.path()});
            }
        }
    }

    p->fileListView.draw(p->fileList);
}

}