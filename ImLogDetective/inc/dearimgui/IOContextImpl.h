
#ifndef IMLOGDETECTIVE_DEARIMGUI_IOCONTEXTIMPL_H
#define IMLOGDETECTIVE_DEARIMGUI_IOCONTEXTIMPL_H

#include "dearimgui/IOContext.h"
#include <memory>

namespace ImLogDetective
{

class IOContextImpl : public IOContext
{
public:
    IOContextImpl();
    ~IOContextImpl();
    void unsetIniFile() final;
    void setFontScale(const float scaleFactor) final;
    bool setFontFromTtfFile(const std::filesystem::path& path) final;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
    
};

}

#endif