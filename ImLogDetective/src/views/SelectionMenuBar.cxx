#include "views/SelectionMenuBar.h"
#include "dearimgui/ScopedImGuiMenuBar.hpp"
#include "ImLogDetectiveDefs.h"

namespace ImLogDetective
{

struct SelectionMenuBar::Impl
{
    Impl(IImGuiMenuBarWrapper& wrapper);
    ~Impl() = default;

    bool folderSelectionClicked;
    bool fetchRemoteLogsClicked;
    bool configureHighlightingClicked;
    int scaleFactor;
    IImGuiMenuBarWrapper& menuBarWrapper;
    std::unique_ptr<ScopedImGuiMenuBar> menuBar;
};

SelectionMenuBar::Impl::Impl(IImGuiMenuBarWrapper& wrapper) :
    folderSelectionClicked{false},
    fetchRemoteLogsClicked{false},
    configureHighlightingClicked{false},
    menuBarWrapper{wrapper},
    menuBar{nullptr},
    scaleFactor{0}
{
}

SelectionMenuBar::SelectionMenuBar(IImGuiMenuBarWrapper& wrapper) :
    p{std::make_unique<Impl>(wrapper)}
{
}

SelectionMenuBar::~SelectionMenuBar() = default;

void SelectionMenuBar::drawSelectionMenuBar()
{
    ScopedImGuiMenuBar(p->menuBarWrapper,{
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
    return std::min(
        Scaling::ScaleFactorLowerBound + (p->scaleFactor * 10.0f) / 100.f, 
        Scaling::ScaleFactorUpperBound);
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