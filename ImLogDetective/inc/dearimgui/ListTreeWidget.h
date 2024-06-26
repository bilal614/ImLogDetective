#pragma once

#include "dearimgui/IListTreeWidget.h"
#include <memory>

namespace ImLogDetective
{

class ListTreeWidget : public IListTreeWidget
{
public:
    ListTreeWidget();
    ~ListTreeWidget();
    void addNode(const std::string& nodeId, std::function<void()> nodeClickedCallback) override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}