#pragma once

#include <memory>

namespace LogAnalyzerTool
{

class IOContext
{
public:
    IOContext();
    ~IOContext();

    void unsetIniFile();
private:
    struct Impl;
    std::unique_ptr<Impl> p;
    
};

}