#pragma once

#include "dearimgui/ITextWidgetFactory.h"
#include <memory>


namespace LogAnalyzerTool
{

class TextWidgetFactory : public ITextWidgetFactory
{
public:
    TextWidgetFactory(); 
    ~TextWidgetFactory();
    void createUnformattedText(const std::string& text) override;
    void createTextColored(const std::string& text, const TextColor& color) override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}