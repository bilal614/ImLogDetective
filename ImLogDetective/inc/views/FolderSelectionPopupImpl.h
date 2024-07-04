
#ifndef IMLOGDETECTIVE_VIEWS_FOLDERSELECTIONPOPUPIMPL_H
#define IMLOGDETECTIVE_VIEWS_FOLDERSELECTIONPOPUPIMPL_H

#include "views/FolderSelectionPopup.h"
#include <memory>
#include <string>

namespace ImLogDetective
{

class ModalPopupFactory;

class FolderSelectionPopupImpl : public FolderSelectionPopup
{
public:
    FolderSelectionPopupImpl(ModalPopupFactory& modalPopup);
    ~FolderSelectionPopupImpl();
    bool setInitialSelectedFolderPath(const std::string& path) final;
    void drawFolderSelectionModalPopup(ImVec2 popupPosition, ImVec2 popupSize) final;
    std::pair<bool, std::filesystem::path> getSelectedFolder() final;
    bool popupOpen() final;
private:
    struct Impl;
    std::unique_ptr<Impl> p;

};

}

#endif