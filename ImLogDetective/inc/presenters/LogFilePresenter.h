
#ifndef IMLOGDETECTIVE_PRESENTERS_LOGFILEPRESENTER_H
#define IMLOGDETECTIVE_PRESENTERS_LOGFILEPRESENTER_H

#include <filesystem>

namespace ImLogDetective
{

class LogDataModel;
class LogFilePresenter
{
public:
    virtual ~LogFilePresenter() = default;
    virtual void update(const std::filesystem::path& filePath, bool readLogFile, LogDataModel& logDataModel) = 0;
};

}

#endif