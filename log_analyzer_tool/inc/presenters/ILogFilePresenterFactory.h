#pragma once

#include <filesystem>

namespace LogAnalyzerTool
{

class ILogFilePresenter;

class ILogFilePresenterFactory
{
public:
    virtual ~ILogFilePresenterFactory() = default;
    virtual std::unique_ptr<ILogFilePresenter> createLogFilePresenter(const std::filesystem::path& filePath) = 0;
};

}