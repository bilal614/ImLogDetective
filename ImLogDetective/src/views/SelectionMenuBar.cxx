#include "views/SelectionMenuBar.h"
#include "dearimgui/ScopedImGuiMenuBar.hpp"
#include "ImLogDetectiveDefs.h"

namespace ImLogDetective
{

struct SelectionMenuBar::Impl
{
    Impl();
    ~Impl() = default;

    bool folderSelectionClicked;
    bool fetchRemoteLogsClicked;
    bool configureHighlightingClicked;
    int scaleFactor;
    std::unique_ptr<ScopedImGuiMenuBar> menuBar;
};

SelectionMenuBar::Impl::Impl() :
    folderSelectionClicked{false},
    fetchRemoteLogsClicked{false},
    configureHighlightingClicked{false},
    menuBar{nullptr},
    scaleFactor{0}
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
    return Scaling::ScaleFactorLowerBound + (p->scaleFactor * 10.0f) / 100.f;
}

bool SelectionMenuBar::copyRemoteLogsClicked()
{
    return p->fetchRemoteLogsClicked;
}

void SelectionMenuBar::copyRemoteLogsClosed()
{
    p->fetchRemoteLogsClicked = false;
}

}