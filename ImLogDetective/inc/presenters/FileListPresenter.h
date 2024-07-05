
#ifndef IMLOGDETECTIVE_PRESENTERS_FILELISTPRESENTER_H
#define IMLOGDETECTIVE_PRESENTERS_FILELISTPRESENTER_H

#include <filesystem>
#include <vector>

namespace ImLogDetective
{

class FileListPresenter
{
public:
    virtual ~FileListPresenter() = default;
    virtual std::vector<std::filesystem::path> getSelectedFiles() = 0;
    virtual void update(const std::filesystem::path& filePath, bool forced) = 0;
};

}

#endif