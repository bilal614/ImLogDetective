#include "presenters/LogFileTabsPresenter.h"
#include "EventHandling/IEvent.h"
#include "presenters/ILogFilePresenter.h"
#include "presenters/ILogDataModelFactory.h"
#include "models/LogDataModel.h"
#include "dearimgui/TabBar.h"

#include <algorithm>
#include <functional>
#include <unordered_map>
#include <vector>

namespace ImLogDetective
{

struct LogFileTabsPresenter::Impl
{
    struct LogFileTab
    {
        LogFileTab(
            const std::filesystem::path& path, 
            bool read, 
            bool isOpen, 
            std::unique_ptr<LogDataModel> dataModel,
            ILogFilePresenter& logFilePresenter) :
                filePath{path},
                readLogFile{read},
                logDataModel{std::move(dataModel)},
                tabBarItem{},
                logFilePresenter{logFilePresenter}
        { 
            tabBarItem.name = filePath.stem();
            tabBarItem.isOpen = isOpen;
            tabBarItem.draw =[&]
            {
                logFilePresenter.update(
                    filePath, 
                    readLogFile, 
                    *logDataModel);
                readLogFile = false;
            
            };
        }
        std::filesystem::path filePath;
        bool readLogFile;
        std::unique_ptr<LogDataModel> logDataModel;
        TabBarItem tabBarItem;
        ILogFilePresenter& logFilePresenter;
    };
    Impl(ILogFilePresenter& logFilePresenter, 
        ILogDataModelFactory& logDataModelFactory, 
        TabBar& tabBar, 
        std::unique_ptr<LogEventHandling::IEvent<const std::string&>> tabsOpenedEvent);
    ~Impl() = default;

    void addTabBarItem(const std::string& name, bool open, const std::filesystem::path& filePath);
    void removeUnselectedTabs(const std::vector<std::filesystem::path>& selectedFiles);

    std::filesystem::path folderPath;
    TabBar& tabBar;
    ILogDataModelFactory& logDataModelFactory;
    std::unordered_map<std::string, std::unique_ptr<LogFileTab>> logFileTabs;
    std::unique_ptr<LogEventHandling::IEvent<const std::string&>> tabsOpened;
    ILogFilePresenter& logFilePresenter;
};

LogFileTabsPresenter::Impl::Impl(ILogFilePresenter& logFilePresenter, 
    ILogDataModelFactory& logDataModelFactory, 
    TabBar& tabBar,
    std::unique_ptr<LogEventHandling::IEvent<const std::string&>> tabsOpenedEvent) :
        folderPath{},
        tabBar{tabBar},
        logDataModelFactory{logDataModelFactory},
        logFilePresenter{logFilePresenter},
        tabsOpened{std::move(tabsOpenedEvent)}
{
}

void LogFileTabsPresenter::Impl::addTabBarItem(
    const std::string& name, 
    bool open, 
    const std::filesystem::path& filePath)
{
    if(logFileTabs.find(name) ==  logFileTabs.end())
    {
        logFileTabs.insert({name, std::make_unique<LogFileTab>(filePath, 
            true,
            open,
            logDataModelFactory.createLogDataModel(name),
            logFilePresenter)});
        tabsOpened->registerDelegate([&](const std::string& name){
            auto tab = logFileTabs.find(name);
            if(tab != logFileTabs.end() && tab->second->tabBarItem.name == name)
            {
                tab->second->tabBarItem.isOpen = true;
            }
        });
    }
}

void LogFileTabsPresenter::Impl::removeUnselectedTabs(const std::vector<std::filesystem::path>& selectedFiles)
{
    for (auto it = logFileTabs.cbegin(); it != logFileTabs.cend();) 
    {
        if(std::find(selectedFiles.begin(), selectedFiles.end(), it->second->filePath) == selectedFiles.end())
        {
            logFileTabs.erase(it++);
        }
        else
        {
            ++it;
        }
    }
}

LogFileTabsPresenter::LogFileTabsPresenter(ILogFilePresenter& logFilePresenter, 
    ILogDataModelFactory& logDataModelFactory, 
    TabBar& tabBar,
    std::unique_ptr<LogEventHandling::IEvent<const std::string&>> tabsOpenedEvent) :
        p{std::make_unique<Impl>(logFilePresenter, logDataModelFactory, tabBar, std::move(tabsOpenedEvent))}
{
}

LogFileTabsPresenter::~LogFileTabsPresenter() = default;

void LogFileTabsPresenter::update(const std::vector<std::filesystem::path>& filePaths)
{
    p->removeUnselectedTabs(filePaths);

    for (const auto& entry : filePaths)
    {
        auto tabName = entry.stem();
        p->addTabBarItem(tabName, false, entry);
    }

    std::vector<std::reference_wrapper<TabBarItem>> tabBarItems;
    for(const auto& logFileTab : p->logFileTabs)
    {
        tabBarItems.push_back(logFileTab.second->tabBarItem);
    }

    if(!tabBarItems.empty())
    {
        p->tabBar.drawTabBar(tabBarItems);
    }
}

LogEventHandling::IEvent<const std::string&>& LogFileTabsPresenter::getTabsOpenedEvent()
{
    return *p->tabsOpened;
}

}