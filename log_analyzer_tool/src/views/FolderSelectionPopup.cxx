#include "views/FolderSelectionPopup.h"
#include "views/IModalPopupFactory.h"
#include "ImLogDetectiveDefs.h"
#include <cstring>
#include <filesystem>

#include "imgui.h"

namespace {

    std::string toString(const char* data)
    {
        return std::string(data, std::strlen(data));
    }
}

namespace ImLogDetective
{

struct FolderSelectionPopup::Impl
{
    Impl(IModalPopupFactory& modalPopupFactory);
    ~Impl() = default;
    bool validateSelectedFolder(const std::filesystem::path& path);
    void processPopupInput(
        bool closeButtonClicked, 
        bool okButtonClicked);
    void closePopup();

    std::filesystem::path selectedFolderPath;
    std::string folderPath;
    bool invalidFolderSelected;
    IModalPopupFactory& modalPopupFactory;
};

FolderSelectionPopup::Impl::Impl(IModalPopupFactory& modalPopupFactory) :
    folderPath(Bounds::MaxTextboxInputLength, '\0'),
    invalidFolderSelected{false},
    modalPopupFactory{modalPopupFactory}
{
}

bool FolderSelectionPopup::Impl::validateSelectedFolder(const std::filesystem::path& path)
{
    return std::filesystem::is_directory(path);
}

void FolderSelectionPopup::Impl::closePopup()
{
    invalidFolderSelected = false;
    modalPopupFactory.close();
}

void FolderSelectionPopup::Impl::processPopupInput(bool okButtonClicked, bool closeButtonClicked)
{
    if (closeButtonClicked)
    {
        closePopup();
        return;
    }
    if(okButtonClicked)
    { 
        selectedFolderPath = std::filesystem::path{folderPath};
        if(invalidFolderSelected = !validateSelectedFolder(std::filesystem::path{folderPath}); !invalidFolderSelected)
        {
            selectedFolderPath = std::filesystem::path{toString(folderPath.data())};
            closePopup();
            return;
        }
    }
    if(invalidFolderSelected)
    {
        modalPopupFactory.showErrorText(ErrorMessage::InvalidDirectory);
    }
}

FolderSelectionPopup::FolderSelectionPopup(IModalPopupFactory& modalPopupFactory) :
    p{std::make_unique<Impl>(modalPopupFactory)}
{
}

FolderSelectionPopup::~FolderSelectionPopup() = default;

bool FolderSelectionPopup::setInitialSelectedFolderPath(const std::string& path)
{
    if(p->validateSelectedFolder(std::filesystem::path{path}))
    {
        p->folderPath = path;
        p->selectedFolderPath = std::filesystem::path{toString(p->folderPath.data())};
        return true;
    }
    return false;
}

void FolderSelectionPopup::drawFolderSelectionModalPopup(ImVec2 popupPosition, ImVec2 popupSize)
{
    p->modalPopupFactory.open(popupPosition, popupSize, SelectFolderDefs::Name);
    p->modalPopupFactory.beginLayout(SelectFolderDefs::Name);
    p->modalPopupFactory.createInputTextBox(SelectFolderDefs::Name, p->folderPath, SelectFolderDefs::TextBoxWidth);

    std::vector<PopupButton> popupButtons = {PopupButton{Common::OkBtn}, PopupButton{Common::CloseBtn}};
    p->modalPopupFactory.createButtonGroup(popupButtons);

    p->modalPopupFactory.endLayout();
    p->processPopupInput(popupButtons[0].clicked, popupButtons[1].clicked);
}

std::pair<bool, std::filesystem::path> FolderSelectionPopup::getSelectedFolder()
{
    return {p->validateSelectedFolder(p->selectedFolderPath), p->selectedFolderPath};
}

bool FolderSelectionPopup::popupOpen()
{
    return p->modalPopupFactory.isPopupOpen();
}

}