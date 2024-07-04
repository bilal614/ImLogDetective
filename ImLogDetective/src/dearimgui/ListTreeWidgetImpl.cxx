
#include "dearimgui/ListTreeWidgetImpl.h"
#include <exception>
#include <memory>
#include <vector>
#include "imgui.h"

namespace ImLogDetective
{

struct ListTreeWidgetImpl::Impl
{
    Impl();
    ~Impl() = default;

    std::vector<std::string> nodeList;
    ImGuiTreeNodeFlags nodeFlags;
};

ListTreeWidgetImpl::Impl::Impl() :
    nodeFlags{ImGuiTreeNodeFlags_OpenOnArrow | 
        ImGuiTreeNodeFlags_OpenOnDoubleClick | 
        ImGuiTreeNodeFlags_SpanAvailWidth | 
        ImGuiTreeNodeFlags_Leaf |
        ImGuiTreeNodeFlags_NoTreePushOnOpen}
{
}

ListTreeWidgetImpl::ListTreeWidgetImpl() :
    p{std::make_unique<Impl>()}
{
}

ListTreeWidgetImpl::~ListTreeWidgetImpl() = default;

void ListTreeWidgetImpl::addNode(const std::string& nodeId, std::function<void()> nodeClickedCallback)
{
    p->nodeList.emplace_back(nodeId);
    ImGui::TreeNodeEx(nodeId.c_str(), p->nodeFlags);
    if (ImGui::IsItemClicked())
    {
        nodeClickedCallback();
    }
}

}