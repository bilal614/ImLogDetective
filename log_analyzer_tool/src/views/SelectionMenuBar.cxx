#include "views/SelectionMenuBar.h"
#include "dearimgui/ScopedImGuiMenuBar.hpp"


namespace LogAnalyzerTool
{

struct SelectionMenuBar::Impl
{
    Impl();
    ~Impl() = default;

    bool folderSelectionClicked;
    bool fetchRemoteLogsClicked;
    float scaleFactor;
    std::unique_ptr<ScopedImGuiMenuBar> menuBar;
};

SelectionMenuBar::Impl::Impl() :
    folderSelectionClicked{false},
    fetchRemoteLogsClicked{false},
    menuBar{nullptr}
{
}

SelectionMenuBar::SelectionMenuBar() :
    p{std::make_unique<Impl>()}
{
}

SelectionMenuBar::~SelectionMenuBar() = default;

void SelectionMenuBar::drawSelectionMenuBar()
{
    ScopedImGuiMenuBar({
        {"Select Folder", std::ref(p->folderSelectionClicked)},
        {"Fetch Remote Logs", std::ref(p->fetchRemoteLogsClicked)}
    }, p->scaleFactor);

}

bool SelectionMenuBar::selectFolderClicked()
{
    return p->folderSelectionClicked;
}

void SelectionMenuBar::selectionFolderClosed()
{
    p->folderSelectionClicked = false;
}

float SelectionMenuBar::getInputScaleFactor()
{
    return p->scaleFactor;
}

}