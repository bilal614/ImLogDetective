#pragma once

#include <string>

struct ImVec2;

namespace LogAnalyzerTool
{

class IModalPopup
{
public:
    virtual ~IModalPopup() = default;
    virtual void open(ImVec2 popupPosition, ImVec2 popupSize, const std::string& name) = 0;
    virtual void close() = 0;
};

}