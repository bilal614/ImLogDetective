#pragma once

#include <string_view>

namespace ImLogDetective
{

struct LogData;
enum class TextColor;

class ILogView
{
public:
    virtual ~ILogView() = default;
    virtual void drawLogLineText(LogData& logLine, const TextColor& color) = 0;
};

}