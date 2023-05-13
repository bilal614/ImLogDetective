#include "views/FolderSelectionMenuBar.h"
#include "dearimgui/ScopedImGuiMenuBar.hpp"


namespace LogAnalyzerTool
{

struct FolderSelectionMenuBar::Impl
{
    Impl();
    ~Impl() = default;

    bool folderSelectionClicked;
    std::unique_ptr<ScopedImGuiMenuBar> menuBar;
};

FolderSelectionMenuBar::Impl::Impl() :
    folderSelectionClicked{false},
    menuBar{nullptr}
{
}

FolderSelectionMenuBar::FolderSelectionMenuBar() :
    p{std::make_unique<Impl>()}
{
}

FolderSelectionMenuBar::~FolderSelectionMenuBar() = default;

void FolderSelectionMenuBar::drawFolderSelectionMenuBar()
{
    ScopedImGuiMenuBar({
        {"Select Folder", std::ref(p->folderSelectionClicked)}
    });
}

bool FolderSelectionMenuBar::selectedFolderClicked()
{
    return p->folderSelectionClicked;
}

void FolderSelectionMenuBar::selectionFolderClosed()
{
    p->folderSelectionClicked = false;
}

}