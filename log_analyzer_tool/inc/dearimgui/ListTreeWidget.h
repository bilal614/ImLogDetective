#pragma once

#include "dearimgui/IListTreeWidget.h"
#include <memory>

namespace LogAnalyzerTool
{

class ListTreeWidget : public IListTreeWidget
{
public:
    ListTreeWidget();
    ~ListTreeWidget();
    void addNode(const std::string& nodeId) override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}