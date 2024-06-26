#pragma once

#include <string_view>

namespace ImLogDetective
{

struct LogLine;
enum class TextColor;

class ILogView
{
public:
    virtual ~ILogView() = default;
    virtual void drawLogLineText(LogLine& logLine) = 0;
};

}