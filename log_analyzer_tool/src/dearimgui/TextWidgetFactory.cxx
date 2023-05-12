
#include "dearimgui/TextWidgetFactory.h"
#include "imgui.h"
#include <unordered_map>

namespace LogAnalyzerTool
{

struct TextWidgetFactory::Impl
{
    Impl();
    ~Impl() = default;
    std::unordered_map<TextColor, ImVec4> colorMap;
};

TextWidgetFactory::Impl::Impl() :
    colorMap{
        {TextColor::Red, ImVec4(1.0f, 0.0f, 0.0f, 1.0f)},
        {TextColor::Orange, ImVec4(1.0f, 0.5f, 0.0f, 1.0f)},
        {TextColor::Yellow, ImVec4(1.0f, 1.0f, 0.0f, 1.0f)},
        {TextColor::Green, ImVec4(0.0f, 1.0f, 0.0f, 1.0f)},
        {TextColor::White, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)},
    }
{

}

TextWidgetFactory::TextWidgetFactory() : 
    p{std::make_unique<Impl>()}
{

}

TextWidgetFactory::~TextWidgetFactory() = default;

void TextWidgetFactory::createUnformattedText(const std::string& text)
{
    ImGui::TextUnformatted(text.c_str());
}

void TextWidgetFactory::createTextColored(std::string_view text, const TextColor& color)
{
    auto textColor = p->colorMap.find(color);
    if(textColor != p->colorMap.end())
    {
        ImGui::TextColored(textColor->second, "%s", text.data());
    }
}

}