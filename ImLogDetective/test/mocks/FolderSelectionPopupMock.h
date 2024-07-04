

#ifndef IMLOGDETECTIVE_VIEWS_FOLDERSELECTIONPOPUPMOCK_H
#define IMLOGDETECTIVE_VIEWS_FOLDERSELECTIONPOPUPMOCK_H

#include "views/FolderSelectionPopup.h"
#include "gmock/gmock.h"
#include "ImVec.h"
#include <utility>

namespace TestImLogDetective {

using ValidFolderPath = std::pair<bool, std::filesystem::path>;

class FolderSelectionPopupMock : public ImLogDetective::FolderSelectionPopup 
{
public:
    MOCK_METHOD(bool, setInitialSelectedFolderPath, (const std::string& path));
    MOCK_METHOD(void, drawFolderSelectionModalPopup, (ImVec2, ImVec2));
    MOCK_METHOD(ValidFolderPath, getSelectedFolder,());
    MOCK_METHOD(bool, popupOpen, ());
};

}

#endif