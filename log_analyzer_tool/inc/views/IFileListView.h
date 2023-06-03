#pragma once


namespace LogAnalyzerTool
{

class IFileListView
{
public:
    virtual ~IFileListView() = default;
    virtual void draw() = 0;
};

}