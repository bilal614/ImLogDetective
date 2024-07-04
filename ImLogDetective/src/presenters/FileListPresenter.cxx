#include "presenters/FileListPresenter.h"
#include "presenters/ILogFileTabsPresenter.h"
#include "views/FileListView.h"
#include <memory>

//REMOVE LATER
#include <iostream>

namespace ImLogDetective
{

struct FileListPresenter::Impl
{
    Impl(ILogFileTabsPresenter& fileTabsPresenter, FileListView& fileListView);
    ~Impl() = default;

    FileListView& fileListView;
    std::filesystem::path folderPath;

    std::unordered_map<std::string, std::filesystem::path> logFiles;
    std::vector<std::string> logFilesList;
    ILogFileTabsPresenter& fileTabsPresenter;
};

FileListPresenter::Impl::Impl(ILogFileTabsPresenter& fileTabsPresenter, FileListView& fileListView) :
    fileListView{fileListView},
    folderPath{},
    fileTabsPresenter{fileTabsPresenter}
{
    fileListView.fileListCallback = [&](const std::string& name){
        fileTabsPresenter.getTabsOpenedEvent()(name);
    };
}

FileListPresenter::FileListPresenter(ILogFileTabsPresenter& fileTabsPresenter, FileListView& fileListView) :
    p{std::make_unique<Impl>(fileTabsPresenter, fileListView)}
{
}

FileListPresenter::~FileListPresenter() = default;

void FileListPresenter::update(const std::filesystem::path& folderPath, bool forced)
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

std::vector<std::filesystem::path> FileListPresenter::getSelectedFiles()
{
    std::vector<std::filesystem::path> selectedFiles;
    std::transform(p->logFiles.begin(), p->logFiles.end(), 
        std::back_inserter(selectedFiles), 
        [](const auto& logFile){return logFile.second; });
    return selectedFiles;
}

}