#pragma once

#include <string>

namespace LogAnalyzerTool
{

enum class TextColor
{
    Red,
    Orange,
    Yellow,
    Green,
    White,
};

class ITextWidgetFactory
{
public:
    virtual ~ITextWidgetFactory() = default;
    virtual void createUnformattedText(const std::string& text) = 0;
    virtual void createTextColored(const std::string& text, const TextColor& color) = 0;
};

}