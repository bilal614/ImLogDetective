#include "presenters/FileListPresenterImpl.h"
#include "LogFileTabsPresenterMock.h"
#include "FileListViewMock.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <filesystem>
#include <fstream>
#include <functional>
#include <ranges>

namespace TestImLogDetective
{

using namespace ::testing;
using ::testing::StrictMock;

class TestFileListPresenterImpl : public ::testing::Test {
protected:
    ::testing::InSequence seq;

    StrictMock<LogFileTabsPresenterMock> logFileTabsPresenterMock;
    StrictMock<FileListViewMock> fileListViewMock;
    std::filesystem::path filePath;
    std::filesystem::path otherFilePath;
    std::vector<std::string> fileNames;
    std::vector<std::string> otherFileNames;
    std::vector<std::filesystem::path> dummyTempFilePaths;

    ImLogDetective::FileListPresenterImpl fileListPresenterImpl;

    void SetUp() override;
    void TearDown() override;

    TestFileListPresenterImpl();
    ~TestFileListPresenterImpl() = default;

private:
    std::filesystem::path initializeTestFolders(const std::string& folderName, const std::vector<std::string>& fileNames);
};

std::filesystem::path TestFileListPresenterImpl::initializeTestFolders(const std::string& folderName, const std::vector<std::string>& fileNames)
{
    auto tempTestFolder = std::filesystem::temp_directory_path() / folderName;
    std::filesystem::remove_all(tempTestFolder);
    std::filesystem::create_directory(tempTestFolder);
    for(const auto& fileName : fileNames)
    {
        auto filePath = tempTestFolder / fileName;
        std::ofstream tmpFile (filePath);
        tmpFile.close();
        dummyTempFilePaths.push_back(filePath);
    }
    return tempTestFolder;
}

TestFileListPresenterImpl::TestFileListPresenterImpl() :
    logFileTabsPresenterMock{},
    fileListViewMock{},
    filePath{},
    otherFilePath{},
    fileNames{"foo", "bar", "bla",},
    otherFileNames{"up", "down", "left", "right"},
    fileListPresenterImpl{logFileTabsPresenterMock, 
        fileListViewMock}
{
}

void TestFileListPresenterImpl::SetUp()
{
    filePath = initializeTestFolders("TestFileListPresenter", fileNames);
    otherFilePath = initializeTestFolders("TestFileListPresenterOther", otherFileNames);
}

void TestFileListPresenterImpl::TearDown()
{
    std::filesystem::remove_all(filePath);
    std::filesystem::remove_all(otherFilePath);
}

TEST_F(TestFileListPresenterImpl, test_FileListPresenterImpl_update_for_given_folder_path) {

    auto expectedFileNames = fileNames;
    std::sort(expectedFileNames.begin(), expectedFileNames.end());
    EXPECT_CALL(fileListViewMock, draw(Eq(expectedFileNames)));
    fileListPresenterImpl.update(filePath, false);

    std::vector<std::filesystem::path> expectedFilePaths;
    std::ranges::copy(std::views::transform(expectedFileNames, [&](const std::string& f){ return filePath / f;}), std::back_inserter(expectedFilePaths));

    std::for_each(expectedFilePaths.begin(), expectedFilePaths.end(), [&](const std::filesystem::path& selectedFile)
    {
        auto selectedFiles = fileListPresenterImpl.getSelectedFiles();
        EXPECT_THAT(selectedFiles, Contains(selectedFile));
    });
}

TEST_F(TestFileListPresenterImpl, test_FileListPresenterImpl_update_when_given_folder_path_changed_to_another_folder) {

    auto expectedFileNames = fileNames;
    std::sort(expectedFileNames.begin(), expectedFileNames.end());

    auto expectedOtherFileNames = otherFileNames;
    std::sort(expectedOtherFileNames.begin(), expectedOtherFileNames.end());


    EXPECT_CALL(fileListViewMock, draw(Eq(expectedFileNames))).Times(1);
    EXPECT_CALL(fileListViewMock, draw(Eq(expectedOtherFileNames))).Times(1);


    fileListPresenterImpl.update(filePath, false);

    std::vector<std::filesystem::path> expectedFilePaths;
    std::ranges::copy(std::views::transform(expectedFileNames, [&](const std::string& f){ return filePath / f;}), std::back_inserter(expectedFilePaths));

    std::for_each(expectedFilePaths.begin(), expectedFilePaths.end(), [&](const std::filesystem::path& selectedFile)
    {
        auto selectedFiles = fileListPresenterImpl.getSelectedFiles();
        EXPECT_THAT(selectedFiles, Contains(selectedFile));
    });


    fileListPresenterImpl.update(otherFilePath, false);

    std::vector<std::filesystem::path> expectedOtherFilePaths;
    std::ranges::copy(std::views::transform(expectedOtherFileNames, [&](const std::string& f){ return otherFilePath / f;}), std::back_inserter(expectedOtherFilePaths));

    std::for_each(expectedOtherFilePaths.begin(), expectedOtherFilePaths.end(), [&](const std::filesystem::path& selectedFile)
    {
        auto selectedFiles = fileListPresenterImpl.getSelectedFiles();
        EXPECT_THAT(selectedFiles, Contains(selectedFile));
    });

}


}