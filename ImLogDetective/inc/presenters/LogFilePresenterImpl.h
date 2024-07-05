
#ifndef IMLOGDETECTIVE_PRESENTERS_LOGFILEPRESENTERIMPL_H
#define IMLOGDETECTIVE_PRESENTERS_LOGFILEPRESENTERIMPL_H

#include <memory>
#include "presenters/LogFilePresenter.h"

namespace LogEventHandling 
{
    class IEventLoop;
}

namespace ImLogDetective
{

class LogDataModel;
class LogFileParser;
class LogFilterView;
class LogView;
class ImGuiTextFilterWrapper;
class WindowFactory;

class LogFilePresenterImpl : public LogFilePresenter
{
public:
    LogFilePresenterImpl(
        WindowFactory& windowFactory,
        LogEventHandling::IEventLoop& eventLoop,
        LogFilterView& logFilterView, 
        LogView& logView,
        LogFileParser& logFileParser,
        ImGuiTextFilterWrapper& textFilterWrapper);
    ~LogFilePresenterImpl();
    void update(const std::filesystem::path& filePath,  bool readLogFile, LogDataModel& logDataModel) override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}

#endif