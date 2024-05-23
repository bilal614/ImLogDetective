#pragma once

#include <memory>
#include <filesystem>

namespace ImLogDetective
{

class IIOContext
{
public:
    virtual ~IIOContext() = default;
    virtual void unsetIniFile() = 0;
    virtual void setFontScale(const float scaleFactor) = 0;
    virtual bool setFontFromTtfFile(const std::filesystem::path& path) = 0;
};

}