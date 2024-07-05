#pragma once

#include "presenters/FileListPresenter.h"
#include "gmock/gmock.h"

namespace TestImLogDetective {

class FileListPresenterMock : public ImLogDetective::FileListPresenter 
{
public:
    MOCK_METHOD(std::vector<std::filesystem::path>, getSelectedFiles,());
    MOCK_METHOD(void, update,(const std::filesystem::path& filePath, bool forced));
};

}