
#ifndef IMLOGDETECTIVE_VIEWS_WIDGETFACTORY_H
#define IMLOGDETECTIVE_VIEWS_WIDGETFACTORY_H

#include "views/ListTreeFactory.h"
#include "views/ModalPopupFactory.h"
#include "views/TextWidgetFactory.h"
#include "views/WindowFactory.h"

namespace ImLogDetective
{

class WidgetFactory : public TextWidgetFactory, public WindowFactory, public ListTreeFactory, public ModalPopupFactory
{
public:
    virtual ~WidgetFactory() = default;
    virtual void onSameLine() = 0;
};

}

#endif