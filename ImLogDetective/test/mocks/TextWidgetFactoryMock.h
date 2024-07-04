
#ifndef IMLOGDETECTIVE_VIEWS_TEXTWIDGETFACTORYMOCK_H
#define IMLOGDETECTIVE_VIEWS_TEXTWIDGETFACTORYMOCK_H

#include "views/TextWidgetFactory.h"
#include "dearimgui/TextColor.h"
#include "gmock/gmock.h"
#include <functional>
#include <string>

namespace TestImLogDetective
{

class TextWidgetFactoryMock : public ImLogDetective::TextWidgetFactory
{
public:
    MOCK_METHOD(void, createUnformattedText,(const std::string&));
    MOCK_METHOD(void, createTextColored,(std::string_view, const ImLogDetective::TextColor&));
    MOCK_METHOD(bool, createSelectedTextColored,(std::string_view, const ImLogDetective::TextColor&, bool));
};

}

#endif