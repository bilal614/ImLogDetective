
#ifndef IMLOGDETECTIVE_DEARIMGUI_LISTTREEWIDGETIMPL_H
#define IMLOGDETECTIVE_DEARIMGUI_LISTTREEWIDGETIMPL_H

#include "dearimgui/ListTreeWidget.h"
#include <memory>

namespace ImLogDetective
{

class ListTreeWidgetImpl : public ListTreeWidget
{
public:
    ListTreeWidgetImpl();
    ~ListTreeWidgetImpl();
    void addNode(const std::string& nodeId, std::function<void()> nodeClickedCallback) override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}

#endif