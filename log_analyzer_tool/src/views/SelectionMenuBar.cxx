#include "views/SelectionMenuBar.h"
#include "dearimgui/ScopedImGuiMenuBar.hpp"
#include "LogAnalyzerToolDefs.h"

namespace LogAnalyzerTool
{

struct SelectionMenuBar::Impl
{
    Impl();
    ~Impl() = default;

    bool folderSelectionClicked;
    bool fetchRemoteLogsClicked;
    bool configureHighlightingClicked;
    float scaleFactor;
    std::unique_ptr<ScopedImGuiMenuBar> menuBar;
};

SelectionMenuBar::Impl::Impl() :
    folderSelectionClicked{false},
    fetchRemoteLogsClicked{false},
    configureHighlightingClicked{false},
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
        {MenuBarOptions::SelectFolder, std::ref(p->folderSelectionClicked)},
        {MenuBarOptions::FetchRemoteLogs, std::ref(p->fetchRemoteLogsClicked)},
        {MenuBarOptions::ConfigureHiglighting, std::ref(p->configureHighlightingClicked)}
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