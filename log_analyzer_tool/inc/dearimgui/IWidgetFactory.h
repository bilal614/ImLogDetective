#pragma once

#include "dearimgui/IListTreeFactory.h"
#include "dearimgui/IModalPopupFactory.h"
#include "dearimgui/ITextWidgetFactory.h"
#include "dearimgui/IWindowFactory.h"

namespace LogAnalyzerTool
{

class IWidgetFactory : public ITextWidgetFactory, public IWindowFactory, public IListTreeFactory, public IModalPopupFactory
{
public:
    virtual ~IWidgetFactory() = default;
    virtual void onSameLine() = 0;
};

}