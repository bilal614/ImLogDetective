#include "views/SelectionMenuBarImpl.h"
#include "dearimgui/ScopedImGuiMenuBar.hpp"
#include "ImLogDetectiveDefs.h"

namespace ImLogDetective
{

struct SelectionMenuBarImpl::Impl
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

SelectionMenuBarImpl::Impl::Impl(IImGuiMenuBarWrapper& wrapper) :
    folderSelectionClicked{false},
    fetchRemoteLogsClicked{false},
    configureHighlightingClicked{false},
    menuBarWrapper{wrapper},
    menuBar{nullptr},
    scaleFactor{0}
{
}

SelectionMenuBarImpl::SelectionMenuBarImpl(IImGuiMenuBarWrapper& wrapper) :
    p{std::make_unique<Impl>(wrapper)}
{
}

SelectionMenuBarImpl::~SelectionMenuBarImpl() = default;

void SelectionMenuBarImpl::drawSelectionMenuBar()
{
    ScopedImGuiMenuBar(p->menuBarWrapper,{
        {MenuBarOptions::SelectFolder, std::ref(p->folderSelectionClicked)},
        {MenuBarOptions::FetchRemoteLogs, std::ref(p->fetchRemoteLogsClicked)},
        {MenuBarOptions::ConfigureHiglighting, std::ref(p->configureHighlightingClicked)}
    }, p->scaleFactor);
}

bool SelectionMenuBarImpl::selectFolderClicked()
{
    return p->folderSelectionClicked;
}

void SelectionMenuBarImpl::selectionFolderClosed()
{
    p->folderSelectionClicked = false;
}

float SelectionMenuBarImpl::getInputScaleFactor()
{
    return std::min(
        Scaling::ScaleFactorLowerBound + (p->scaleFactor * 10.0f) / 100.f, 
        Scaling::ScaleFactorUpperBound);
}

bool SelectionMenuBarImpl::copyRemoteLogsClicked()
{
    return p->fetchRemoteLogsClicked;
}

void SelectionMenuBarImpl::copyRemoteLogsClosed()
{
    p->fetchRemoteLogsClicked = false;
}

}