#pragma once

#include <string_view>

namespace ImLogDetective
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
    virtual void createTextColored(std::string_view text, const TextColor& color) = 0;
    virtual bool createSelectedTextColored(std::string_view text, const TextColor& color, bool selected) = 0;
};

}