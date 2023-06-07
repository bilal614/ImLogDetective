
#include "dearimgui/ListTreeWidget.h"
#include <exception>
#include <memory>
#include <vector>
#include "imgui.h"

//REMOVE LATER
#include <iostream>

namespace LogAnalyzerTool
{

struct ListTreeWidget::Impl
{
    Impl();
    ~Impl() = default;

    std::vector<std::string> nodeList;
    ImGuiTreeNodeFlags nodeFlags;
};

ListTreeWidget::Impl::Impl() :
    nodeFlags{ImGuiTreeNodeFlags_OpenOnArrow | 
        ImGuiTreeNodeFlags_OpenOnDoubleClick | 
        ImGuiTreeNodeFlags_SpanAvailWidth | 
        ImGuiTreeNodeFlags_Leaf |
        ImGuiTreeNodeFlags_NoTreePushOnOpen}
{
}

ListTreeWidget::ListTreeWidget() :
    p{std::make_unique<Impl>()}
{
}

ListTreeWidget::~ListTreeWidget() = default;

void ListTreeWidget::addNode(const std::string& nodeId)
{
    p->nodeList.emplace_back(nodeId);
    ImGui::TreeNodeEx(nodeId.c_str(), p->nodeFlags);
    if (ImGui::IsItemClicked())
    {
        //TODO in future introduce event loop for running actions/tasks on separate thread not UI thread
    }
}

}