#pragma once

namespace LogAnalyzerTool
{

class IMainPresenter
{
public:
    virtual ~IMainPresenter() = default;
    virtual void update() = 0;
};

}