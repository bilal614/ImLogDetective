#include "presenters/FileListPresenterImpl.h"
#include "presenters/LogFileTabsPresenter.h"
#include "views/FileListView.h"
#include <memory>

//REMOVE LATER
#include <iostream>

namespace ImLogDetective
{

struct FileListPresenterImpl::Impl
{
    Impl(LogFileTabsPresenter& fileTabsPresenter, FileListView& fileListView);
    ~Impl() = default;

    FileListView& fileListView;
    std::filesystem::path folderPath;

    std::unordered_map<std::string, std::filesystem::path> logFiles;
    std::vector<std::string> logFilesList;
    LogFileTabsPresenter& fileTabsPresenter;
};

FileListPresenterImpl::Impl::Impl(LogFileTabsPresenter& fileTabsPresenter, FileListView& fileListView) :
    fileListView{fileListView},
    folderPath{},
    fileTabsPresenter{fileTabsPresenter}
{
    fileListView.fileListCallback = [&](const std::string& name){
        fileTabsPresenter.getTabsOpenedEvent()(name);
    };
}

FileListPresenterImpl::FileListPresenterImpl(LogFileTabsPresenter& fileTabsPresenter, FileListView& fileListView) :
    p{std::make_unique<Impl>(fileTabsPresenter, fileListView)}
{
}

FileListPresenterImpl::~FileListPresenterImpl() = default;

void FileListPresenterImpl::update(const std::filesystem::path& folderPath, bool forced)
{
    bool folderPathChanged = false;
    if(p->folderPath != folderPath || forced)
    {
        folderPathChanged = true;
        p->folderPath = folderPath;
        p->logFiles.clear();
        p->logFilesList.clear();
        for (const auto& entry : std::filesystem::directory_iterator(p->folderPath))
        {
            if(entry.is_regular_file())
            {
                auto tabName = entry.path().stem();
                p->logFiles.insert({tabName, entry.path()});
            }
        }

        std::transform(p->logFiles.cbegin(), p->logFiles.cend(), std::back_inserter(p->logFilesList), 
            [&](const auto& logFile){
                return logFile.first;
            });
        std::sort(p->logFilesList.begin(), p->logFilesList.end());
    }
    p->fileListView.draw(p->logFilesList);
}

std::vector<std::filesystem::path> FileListPresenterImpl::getSelectedFiles()
{
    std::vector<std::filesystem::path> selectedFiles;
    std::transform(p->logFiles.begin(), p->logFiles.end(), 
        std::back_inserter(selectedFiles), 
        [](const auto& logFile){return logFile.second; });
    return selectedFiles;
}

}