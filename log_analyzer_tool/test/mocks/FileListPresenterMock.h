#pragma once

#include "presenters/IFileListPresenter.h"
#include "gmock/gmock.h"

namespace TestLogAnalyzerTool {

class FileListPresenterMock : public LogAnalyzerTool::IFileListPresenter 
{
public:
    MOCK_METHOD(std::vector<std::filesystem::path>, getSelectedFiles,());
    MOCK_METHOD(void, update,(const std::filesystem::path& filePath));
};

}