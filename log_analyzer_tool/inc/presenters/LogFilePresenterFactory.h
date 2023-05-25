#pragma once

#include "presenters/ILogFilePresenter.h"
#include "presenters/ILogFilePresenterFactory.h"
#include <memory>

namespace LogAnalyzerTool
{

class ILogFileParser;
class ILogFilterView;
class ILogView;
class IWindowFactory;

class LogFilePresenterFactory : public ILogFilePresenterFactory
{
public:
    LogFilePresenterFactory(IWindowFactory& windowFactory,
        ILogFilterView& logFilterView, 
        ILogView& logView,
        ILogFileParser& logFileParser);
    ~LogFilePresenterFactory();
    std::unique_ptr<ILogFilePresenter> createLogFilePresenter(const std::filesystem::path& filePath) override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}