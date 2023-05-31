#include "LogAnalyzerToolDefs.h"
#include "presenters/LogFileTabsPresenter.h"
#include "mocks/LogFilePresenterFactoryMock.h"
#include "mocks/TabBarMock.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <filesystem>
#include <fstream>
#include <gmock/gmock-spec-builders.h>

namespace TestLogAnalyzerTool
{

using ::testing::StrictMock;

class TestLogFileTabsPresenter : public ::testing::Test {
protected:
    ::testing::InSequence seq;

    LogFilePresenterFactoryMock logFilePresenterFactoryMock;
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
    logFilePresenterFactoryMock{},
    tabBarMock{},
    filePath{},
    dummyTempFileNames{"foo", "bar", "bla"},
    logFileTabsPresenter{logFilePresenterFactoryMock, tabBarMock}
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
        EXPECT_CALL(logFilePresenterFactoryMock, createLogFilePresenter(filePath / fileName));
    }
    EXPECT_CALL(tabBarMock, drawTabBar(::testing::_));

    logFileTabsPresenter.update(filePath);
}

}