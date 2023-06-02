#include "presenters/LogFileTabsPresenter.h"
#include "presenters/ILogFilePresenter.h"
#include "presenters/ILogDataModelFactory.h"
#include "models/ILogDataModel.h"
#include "dearimgui/ITabBar.h"

#include <functional>
#include <unordered_map>
#include <vector>

namespace LogAnalyzerTool
{

struct LogFileTabsPresenter::Impl
{
    struct LogFileData
    {
        LogFileData(const std::filesystem::path& filePath, bool read, std::unique_ptr<ILogDataModel> logDataModel) :
            filePath{filePath},
            readLogFile{read},
            logDataModel{std::move(logDataModel)}
        { }
        std::filesystem::path filePath;
        bool readLogFile;
        std::unique_ptr<ILogDataModel> logDataModel;
    };
    Impl(ILogFilePresenter& logFilePresenter, ILogDataModelFactory& logDataModelFactory, ITabBar& tabBar);
    ~Impl() = default;

    void addTabBarItem(const std::string& name, bool open, const std::filesystem::path& filePath);

    std::filesystem::path folderPath;
    ITabBar& tabBar;
    ILogDataModelFactory& logDataModelFactory;
    std::unordered_map<std::string, std::unique_ptr<LogFileData>> tabLogFilePath;
    std::vector<TabBarItem> tabBarItems;

    ILogFilePresenter& logFilePresenter;
};

LogFileTabsPresenter::Impl::Impl(ILogFilePresenter& logFilePresenter, ILogDataModelFactory& logDataModelFactory, ITabBar& tabBar) :
    folderPath{},
    tabBar{tabBar},
    logDataModelFactory{logDataModelFactory},
    logFilePresenter{logFilePresenter}
{
}

void LogFileTabsPresenter::Impl::addTabBarItem(const std::string& name, bool open, const std::filesystem::path& filePath)
{
    tabLogFilePath.insert({name, std::make_unique<LogFileData>(filePath, true, logDataModelFactory.createLogFilePresenter(name))});
    tabBarItems.emplace_back(TabBarItem{name, open, [&, name]
    {
        if(tabLogFilePath.find(name) != tabLogFilePath.end())
        {
            logFilePresenter.update(
                tabLogFilePath[name]->filePath, 
                tabLogFilePath[name]->readLogFile, 
                *tabLogFilePath[name]->logDataModel);
            tabLogFilePath[name]->readLogFile = false;
        }
    }});
}

LogFileTabsPresenter::LogFileTabsPresenter(ILogFilePresenter& logFilePresenter, ILogDataModelFactory& logDataModelFactory, ITabBar& tabBar) :
    p{std::make_unique<Impl>(logFilePresenter, logDataModelFactory, tabBar)}
{
}

LogFileTabsPresenter::~LogFileTabsPresenter() = default;

void LogFileTabsPresenter::update(const std::filesystem::path& folderPath)
{
    bool folderPathChanged = false;
    if(p->folderPath != folderPath)
    {
        folderPathChanged = true;
        p->folderPath = folderPath;

        p->tabLogFilePath.clear();
        p->tabBarItems.clear();

        for (const auto& entry : std::filesystem::directory_iterator(p->folderPath))
        {
            if(entry.is_regular_file())
            {
                auto tabName = entry.path().stem();
                p->addTabBarItem(tabName, true, entry);
            }
        }
    }

    if(!p->folderPath.empty())
    {
        p->tabBar.drawTabBar(p->tabBarItems);
    }
}

}