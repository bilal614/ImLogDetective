#include "ImLogDetectiveDefs.h"
#include "dearimgui/ITabBar.h"
#include "presenters/LogFileTabsPresenter.h"
#include "EventMock.h"
#include "LogFilePresenterMock.h"
#include "LogDataModelFactoryMock.h"
#include "TabBarMock.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <filesystem>
#include <fstream>
#include <functional>
#include <gmock/gmock-more-actions.h>
#include <gmock/gmock-spec-builders.h>

namespace TestImLogDetective
{

using namespace ::testing;
using ::testing::StrictMock;

class TestLogFileTabsPresenter : public ::testing::Test {
protected:
    ::testing::InSequence seq;

    StrictMock<LogDataModelFactoryMock> logDataModelFactoryMock;
    StrictMock<LogFilePresenterMock> logFilePresenterMock;
    StrictMock<TabBarMock> tabBarMock;
    std::filesystem::path filePath;
    std::vector<std::filesystem::path> dummyTempFilePaths;

    ImLogDetective::LogFileTabsPresenter logFileTabsPresenter;

    void SetUp() override;
    void TearDown() override;

    TestLogFileTabsPresenter();
    ~TestLogFileTabsPresenter() = default;
};

TestLogFileTabsPresenter::TestLogFileTabsPresenter() :
    logFilePresenterMock{},
    tabBarMock{},
    filePath{},
    logFileTabsPresenter{logFilePresenterMock, 
        logDataModelFactoryMock,
        tabBarMock, 
        std::move(std::make_unique<EventMock<const std::string&>>())}
{
}

void TestLogFileTabsPresenter::SetUp()
{
    auto tempTestFolder = std::filesystem::temp_directory_path() / "TestLogFileTabsPresenter";
    std::filesystem::remove_all(tempTestFolder);
    std::filesystem::create_directory(tempTestFolder);
    for(const auto& fileName : {"foo", "bar", "bla"})
    {
        auto filePath = tempTestFolder / fileName;
        std::ofstream tmpFile (filePath);
        tmpFile.close();
        dummyTempFilePaths.push_back(filePath);
    }

    filePath = tempTestFolder;
}

void TestLogFileTabsPresenter::TearDown()
{
    std::filesystem::remove_all(filePath);
}

TEST_F(TestLogFileTabsPresenter, test_LogFileTabsPresenter_update) {

    auto& tabsOpenedEvent = dynamic_cast<EventMock<const std::string&>&>(logFileTabsPresenter.getTabsOpenedEvent());
    for(const auto& filePath : dummyTempFilePaths)
    {
        EXPECT_CALL(logDataModelFactoryMock, createLogDataModel(filePath.stem().string()));
        EXPECT_CALL(tabsOpenedEvent, registerDelegate(::testing::_));
    }
    std::vector<std::reference_wrapper<ImLogDetective::TabBarItem>> data;

    EXPECT_CALL(tabBarMock, drawTabBar(::testing::_)).WillOnce(DoAll(::testing::SaveArg<0>(&data)));

    logFileTabsPresenter.update(dummyTempFilePaths);

    EXPECT_EQ(data.size(), dummyTempFilePaths.size());

    for(const auto& filePath : dummyTempFilePaths)
    {
        auto it = std::find_if(data.begin(), data.end(), [&](std::reference_wrapper<ImLogDetective::TabBarItem> item){
            return item.get().name == filePath.stem().string();
        });
        EXPECT_NE(data.end(), it);
        EXPECT_FALSE(it->get().isOpen);
    }
}

}