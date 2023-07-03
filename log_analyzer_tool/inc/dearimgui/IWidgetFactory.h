#pragma once

#include "dearimgui/IListTreeFactory.h"
#include "dearimgui/ITextWidgetFactory.h"
#include "dearimgui/IWindowFactory.h"

namespace LogAnalyzerTool
{

class IWidgetFactory : public ITextWidgetFactory, public IWindowFactory, public IListTreeFactory
{
public:
    virtual ~IWidgetFactory() = default;
    virtual void onSameLine() = 0;
};

}