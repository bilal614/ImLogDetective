#include "LogAnalyzerToolDefs.h"
#include "dearimgui/ITabBar.h"
#include "presenters/LogFileTabsPresenter.h"
#include "mocks/LogFilePresenterMock.h"
#include "mocks/LogDataModelFactoryMock.h"
#include "mocks/TabBarMock.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <filesystem>
#include <fstream>
#include <gmock/gmock-more-actions.h>
#include <gmock/gmock-spec-builders.h>

namespace TestLogAnalyzerTool
{

using ::testing::StrictMock;

class TestLogFileTabsPresenter : public ::testing::Test {
protected:
    ::testing::InSequence seq;

    LogDataModelFactoryMock logDataModelFactoryMock;
    LogFilePresenterMock logFilePresenterMock;
    TabBarMock tabBarMock;
    std::filesystem::path filePath;
    std::vector<std::string> dummyTempFileNames;

    LogAnalyzerTool::LogFileTabsPresenter logFileTabsPresenter;

    void SetUp() override;
    void TearDown() override;

    TestLogFileTabsPresenter();
    ~TestLogFileTabsPresenter() = default;
};

TestLogFileTabsPresenter::TestLogFileTabsPresenter() :
    logFilePresenterMock{},
    tabBarMock{},
    filePath{},
    dummyTempFileNames{"foo", "bar", "bla"},
    logFileTabsPresenter{logFilePresenterMock, logDataModelFactoryMock, tabBarMock}
{
    std::sort(dummyTempFileNames.begin(),dummyTempFileNames.end(),
        [&](std::string lhs, std::string rhs) {return lhs > rhs;});
}

void TestLogFileTabsPresenter::SetUp()
{
    auto tempTestFolder = std::filesystem::temp_directory_path() / "TestLogFileTabsPresenter";
    std::filesystem::remove_all(tempTestFolder);
    std::filesystem::create_directory(tempTestFolder);
    for(const auto& fileName : dummyTempFileNames)
    {
        std::ofstream tmpFile (tempTestFolder / fileName);
        tmpFile.close();
    }

    filePath = tempTestFolder;
}

void TestLogFileTabsPresenter::TearDown()
{
    std::filesystem::remove_all(filePath);
}

TEST_F(TestLogFileTabsPresenter, test_LogFileTabsPresenter_update) {

    for(const auto& fileName : dummyTempFileNames)
    {
        EXPECT_CALL(logDataModelFactoryMock, createLogFilePresenter(fileName));
    }
    std::vector<LogAnalyzerTool::TabBarItem> data;

    EXPECT_CALL(tabBarMock, drawTabBar(::testing::_)).WillOnce(DoAll(::testing::SaveArg<0>(&data)));

    logFileTabsPresenter.update(filePath);

    EXPECT_EQ(data.size(), dummyTempFileNames.size());

    size_t index = 0;
    for(const auto& name : dummyTempFileNames)
    {
        EXPECT_EQ(data[index].name, name);
        EXPECT_TRUE(data[index++].isOpen);
    }
}

}