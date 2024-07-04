
#ifndef IMLOGDETECTIVE_DEARIMGUI_LISTTREEWIDGET_H
#define IMLOGDETECTIVE_DEARIMGUI_LISTTREEWIDGET_H

#include <functional>
#include <string>

namespace ImLogDetective
{

class ListTreeWidget
{
public:
    virtual ~ListTreeWidget() = default;
    virtual void addNode(const std::string& nodeId, std::function<void()> nodeClickedCallback) = 0;
};

}

#endif