
#ifndef IMLOGDETECTIVE_VIEWS_WINDOWFACTORYMOCK_H
#define IMLOGDETECTIVE_VIEWS_WINDOWFACTORYMOCK_H

#include "views/WindowFactory.h"
#include "gmock/gmock.h"

namespace TestImLogDetective {

class WindowFactoryMock : public ImLogDetective::WindowFactory 
{
public:
    MOCK_METHOD(std::unique_ptr<ImLogDetective::IScopedImGuiWindow>, createWindow, ());
    MOCK_METHOD(std::unique_ptr<ImLogDetective::IScopedImGuiWindow>, createChildWindow, (
        const std::string&, 
        const ImVec2&,
        const ImVec2&));

};

}

#endif