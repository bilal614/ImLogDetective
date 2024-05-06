#pragma once

#include <filesystem>

namespace LogAnalyzerTool
{

class IMini 
{
public:
    virtual~IMini() = default;
    virtual void set(const std::string& section, const std::string& name, const std::string& value) = 0;
    virtual std::string get(const std::string& section, const std::string& name) = 0;
    virtual void updateIniFile() = 0;
};

}