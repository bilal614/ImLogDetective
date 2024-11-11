#include "models/MiniImpl.h"
#include "gtest/gtest.h"
#include <filesystem>
#include "TestUtility.h"

namespace TestImLogDetective
{

TEST(TestMiniImpl, test_MiniImpl_getter_and_setter) 
{
    auto testFolderPath = TestUtility::getTestDataFolder()/std::filesystem::path("TestFolderSelectionPopup");
    std::filesystem::create_directories(testFolderPath);
    auto iniFilePath = testFolderPath/"foo.ini";

    ImLogDetective::MiniImpl miniImpl{iniFilePath};

    miniImpl.set("Test Section", "foo", "bar");
    EXPECT_EQ(miniImpl.get("Test Section", "foo"), "bar");

    miniImpl.set("Test Section", "777", "down");
    EXPECT_EQ(miniImpl.get("Test Section", "777"), "down");

    miniImpl.set("Another Test Section", "314", "up");
    EXPECT_EQ(miniImpl.get("Test Section", "314"), "");
    EXPECT_EQ(miniImpl.get("Another Test Section", "314"), "up");

    EXPECT_TRUE(miniImpl.updateIniFile());

    std::filesystem::remove_all(testFolderPath);
}

}