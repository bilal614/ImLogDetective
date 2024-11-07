#pragma once
#include "gmock/gmock.h"
#include <filesystem>

namespace TestImLogDetective
{

MATCHER_P(imvec2_equal, a, "") { return arg.x == a.x && arg.y == a.y; };

class TestUtility {

public:
    static std::filesystem::path getTestDataFolder();
    static std::filesystem::path getTestExecutablePath();

};

}