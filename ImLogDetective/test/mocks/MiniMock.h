#pragma once

#include "models/Mini.h"
#include <gmock/gmock.h>


namespace TestImLogDetective {

class MiniMock : public ImLogDetective::Mini 
{
public:
    MOCK_METHOD(void, set, (const std::string& section, const std::string& name, const std::string& value));
    MOCK_METHOD(std::string, get, (const std::string& section, const std::string& name), (const));
    MOCK_METHOD(bool, updateIniFile,());
};

}