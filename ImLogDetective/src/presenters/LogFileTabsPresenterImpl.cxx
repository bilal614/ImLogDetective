#include "presenters/LogFileTabsPresenterImpl.h"
#include "EventHandling/IEvent.h"
#include "presenters/LogFilePresenter.h"
#include "presenters/LogDataModelFactory.h"
#include "models/LogDataModel.h"
#include "dearimgui/TabBar.h"

#include <algorithm>
#include <functional>
#include <unordered_map>
#include <vector>

namespace ImLogDetective
{

struct LogFileTabsPresenterImpl::Impl
{
    struct LogFileTab
    {
        LogFileTab(
            const std::filesystem::path& path, 
            bool read, 
            bool isOpen, 
            std::unique_ptr<LogDataModel> dataModel,
            LogFilePresenter& logFilePresenter) :
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
        LogFilePresenter& logFilePresenter;
    };
    Impl(LogFilePresenter& logFilePresenter, 
        LogDataModelFactory& logDataModelFactory, 
        TabBar& tabBar, 
        std::unique_ptr<LogEventHandling::IEvent<const std::string&>> tabsOpenedEvent);
    ~Impl() = default;

    void addTabBarItem(const std::string& name, bool open, const std::filesystem::path& filePath);
    void removeUnselectedTabs(const std::vector<std::filesystem::path>& selectedFiles);

    std::filesystem::path folderPath;
    TabBar& tabBar;
    LogDataModelFactory& logDataModelFactory;
    std::unordered_map<std::string, std::unique_ptr<LogFileTab>> logFileTabs;
    std::unique_ptr<LogEventHandling::IEvent<const std::string&>> tabsOpened;
    LogFilePresenter& logFilePresenter;
};

LogFileTabsPresenterImpl::Impl::Impl(LogFilePresenter& logFilePresenter, 
    LogDataModelFactory& logDataModelFactory, 
    TabBar& tabBar,
    std::unique_ptr<LogEventHandling::IEvent<const std::string&>> tabsOpenedEvent) :
        folderPath{},
        tabBar{tabBar},
        logDataModelFactory{logDataModelFactory},
        logFilePresenter{logFilePresenter},
        tabsOpened{std::move(tabsOpenedEvent)}
{
}

void LogFileTabsPresenterImpl::Impl::addTabBarItem(
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

void LogFileTabsPresenterImpl::Impl::removeUnselectedTabs(const std::vector<std::filesystem::path>& selectedFiles)
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

LogFileTabsPresenterImpl::LogFileTabsPresenterImpl(LogFilePresenter& logFilePresenter, 
    LogDataModelFactory& logDataModelFactory, 
    TabBar& tabBar,
    std::unique_ptr<LogEventHandling::IEvent<const std::string&>> tabsOpenedEvent) :
        p{std::make_unique<Impl>(logFilePresenter, logDataModelFactory, tabBar, std::move(tabsOpenedEvent))}
{
}

LogFileTabsPresenterImpl::~LogFileTabsPresenterImpl() = default;

void LogFileTabsPresenterImpl::update(const std::vector<std::filesystem::path>& filePaths)
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

LogEventHandling::IEvent<const std::string&>& LogFileTabsPresenterImpl::getTabsOpenedEvent()
{
    return *p->tabsOpened;
}

}