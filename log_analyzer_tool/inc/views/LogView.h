#pragma once

#include "views/ILogView.h"

#include <memory>
#include <string_view>

namespace ImLogDetective
{

class ITextWidgetFactory;

class LogView : public ILogView
{
public:
    LogView(ITextWidgetFactory& textWidgetFactory);
    ~LogView();
    void drawLogLineText(std::string_view logText, const TextColor& color) override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}