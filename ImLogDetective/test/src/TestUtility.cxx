#include "TestUtility.h"
#include <unistd.h>

namespace TestImLogDetective
{

std::filesystem::path TestUtility::getTestExecutablePath()
{
    char buffer[1048] = {'\0'};
    readlink("/proc/self/exe", buffer, 1048);
    return std::filesystem::path{buffer}.remove_filename(); 
}

std::filesystem::path TestUtility::getTestDataFolder()
{
    return getTestExecutablePath().append("test_data");
}

}