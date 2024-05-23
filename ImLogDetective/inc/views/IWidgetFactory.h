#pragma once

#include "views/IListTreeFactory.h"
#include "views/IModalPopupFactory.h"
#include "views/ITextWidgetFactory.h"
#include "views/IWindowFactory.h"

namespace ImLogDetective
{

class IWidgetFactory : public ITextWidgetFactory, public IWindowFactory, public IListTreeFactory, public IModalPopupFactory
{
public:
    virtual ~IWidgetFactory() = default;
    virtual void onSameLine() = 0;
};

}