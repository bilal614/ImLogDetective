#pragma once
#include <filesystem>

namespace TestLogAnalyzerTool
{

class TestUtility {

public:
    TestUtility();
    ~TestUtility();

    static std::filesystem::path getTestDataFolder();
    static std::filesystem::path getTestExecutablePath();

};

}