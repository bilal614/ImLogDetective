#include "presenters/LogFileTabsPresenter.h"
#include "presenters/ILogFilePresenter.h"
#include "presenters/ILogFilePresenterFactory.h"
#include "dearimgui/ITabBar.h"

#include <functional>
#include <unordered_map>
#include <vector>

namespace LogAnalyzerTool
{

struct LogFileTabsPresenter::Impl
{
    struct LogFileTabItem
    {
        std::string name;
        bool isOpen;
        bool readLogFile;
        std::filesystem::path logFilePath;
        std::unique_ptr<ILogFilePresenter> logFilePresenter;

        std::tuple<std::string, bool, std::function<void()>> getItem()
        {
            bool logFileContentsRead = readLogFile;
            readLogFile = false;
            return std::tuple(name, isOpen, [&]{
                logFilePresenter->update(logFilePath);
            });
        }
    };

    Impl(ILogFilePresenterFactory& logFilePresenterFactory, ITabBar& tabBar);
    ~Impl() = default;

    std::filesystem::path folderPath;
    ITabBar& tabBar;
    ILogFilePresenterFactory& logFilePresenterFactory;
    std::unordered_map<std::string, LogFileTabItem> logFileTabItems;
};

LogFileTabsPresenter::Impl::Impl(ILogFilePresenterFactory& logFilePresenterFactory, ITabBar& tabBar) :
    folderPath{},
    tabBar{tabBar},
    logFilePresenterFactory{logFilePresenterFactory}
{
}

LogFileTabsPresenter::LogFileTabsPresenter(ILogFilePresenterFactory& logFilePresenterFactory, ITabBar& tabBar) :
    p{std::make_unique<Impl>(logFilePresenterFactory, tabBar)}
{
}

LogFileTabsPresenter::~LogFileTabsPresenter() = default;

void LogFileTabsPresenter::update(const std::filesystem::path& folderPath)
{
    std::vector<std::tuple<std::string, bool, std::function<void()>>> tabItemsToDraw;
    bool folderPathChanged = false;
    if(p->folderPath != folderPath)
    {
        folderPathChanged = true;
        p->folderPath = folderPath;

        p->logFileTabItems.clear();
        for (const auto& entry : std::filesystem::directory_iterator(p->folderPath))
        {
            if(entry.is_regular_file())
            {
                auto tabName = entry.path().stem();
                p->logFileTabItems.insert({tabName, 
                    Impl::LogFileTabItem{tabName, true, true, entry.path(),
                    p->logFilePresenterFactory.createLogFilePresenter(entry.path())}});
                tabItemsToDraw.emplace_back(p->logFileTabItems[tabName].getItem());
            }
        }
    } else {
        for(auto& logFileTabItem: p->logFileTabItems)
        {
            tabItemsToDraw.emplace_back(logFileTabItem.second.getItem());
        }
    }

    if(!p->folderPath.empty())
    {
        p->tabBar.drawTabBar(tabItemsToDraw);
    }
}

}