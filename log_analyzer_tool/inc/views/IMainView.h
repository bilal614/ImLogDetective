#pragma once

namespace LogAnalyzerTool
{

class IMainView
{
public:
    virtual ~IMainView() = default;
    virtual void show() = 0;
};

}