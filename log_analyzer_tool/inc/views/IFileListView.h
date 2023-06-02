#pragma once

#include <string_view>

namespace LogAnalyzerTool
{

class IFileListView
{
public:
    virtual ~IFileListView() = default;
    virtual void draw() = 0;
};

}