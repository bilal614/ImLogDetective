
#ifndef IMLOGDETECTIVE_DEARIMGUI_IOCONTEXT_H
#define IMLOGDETECTIVE_DEARIMGUI_IOCONTEXT_H

#include <memory>
#include <filesystem>

namespace ImLogDetective
{

class IOContext
{
public:
    virtual ~IOContext() = default;
    virtual void unsetIniFile() = 0;
    virtual void setFontScale(const float scaleFactor) = 0;
    virtual bool setFontFromTtfFile(const std::filesystem::path& path) = 0;
};

}

#endif