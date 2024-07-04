
#ifndef IMLOGDETECTIVE_VIEWS_TEXTWIDGETFACTORY_H
#define IMLOGDETECTIVE_VIEWS_TEXTWIDGETFACTORY_H

#include <string_view>

namespace ImLogDetective
{

enum class TextColor;

class TextWidgetFactory
{
public:
    virtual ~TextWidgetFactory() = default;
    virtual void createUnformattedText(const std::string& text) = 0;
    virtual void createTextColored(std::string_view text, const TextColor& color) = 0;
    virtual bool createSelectedTextColored(std::string_view text, const TextColor& color, bool selected) = 0;
};

}

#endif