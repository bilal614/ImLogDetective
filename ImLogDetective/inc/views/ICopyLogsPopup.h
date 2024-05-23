#pragma once

#include "views/IPopup.h"
#include <filesystem>
#include <utility>

struct ImVec2;

namespace ImLogDetective
{

struct CopyLogs{
    CopyLogs() :
        srcHostPath(1024, '\0'),
        dstDirectory(1024, '\0'),
        jumpHostPath1(1024, '\0'),
        jumpHostPath2(1024, '\0'),
        keyFile1(1024, '\0'),
        keyFile2(1024, '\0')
    {}
    std::string srcHostPath;
    std::string dstDirectory;

    std::string jumpHostPath1;
    std::string jumpHostPath2;

    std::string keyFile1;
    std::string keyFile2;
};

class ICachedCopyLogsPopupInput 
{
    public:
        virtual ~ICachedCopyLogsPopupInput() = default;
        virtual void initInput(const CopyLogs& input) = 0;
};

class ICopyLogsPopup : public IPopup<CopyLogs>, public ICachedCopyLogsPopupInput
{
};

}