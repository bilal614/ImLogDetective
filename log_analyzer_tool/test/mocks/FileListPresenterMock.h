#pragma once

#include "presenters/IFileListPresenter.h"
#include "gmock/gmock.h"

namespace TestImLogDetective {

class FileListPresenterMock : public ImLogDetective::IFileListPresenter 
{
public:
    MOCK_METHOD(std::vector<std::filesystem::path>, getSelectedFiles,());
    MOCK_METHOD(void, update,(const std::filesystem::path& filePath));
};

}