#pragma once
#include "gmock/gmock.h"
#include <filesystem>

namespace TestImLogDetective
{

MATCHER_P(imvec2_equal, a, "") { return arg.x == a.x && arg.y == a.y; };
MATCHER_P(imvec4_equal, a, "") { return arg.x == a.x && arg.y == a.y && arg.z == a.z && arg.w == a.w; };

class TestUtility {

public:
    static std::filesystem::path getTestDataFolder();
    static std::filesystem::path getTestExecutablePath();

};

}