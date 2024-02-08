#include "gtest/gtest.h"
#include <filesystem>
#include "models/GzipFile.h"
#include "TestUtility.h"
namespace TestLogAnalyzerTool
{

TEST(TestGzipFileParser, test_gzip_file_parser) 
{
    LogAnalyzerTool::GzipFile gzipFileParser;
    std::vector<std::string> expectedLines{"hello world 1", 
        "hello world 2", 
        "hello world 3", 
        "foo bar", 
        "bar foo", 
        "bla bla bla"};

    std::filesystem::path testData{TestUtility::getTestDataFolder().append("test.txt.gz")};

    auto result = gzipFileParser.decompress(testData);

    std::string line;
    auto lineCount = 0;
    while (std::getline(result, line))
    {
        EXPECT_EQ(line, expectedLines[lineCount]);
        ++lineCount;
    }
}

}