#pragma once

#include "views/IWindowFactory.h"
#include "gmock/gmock.h"

namespace TestImLogDetective {

class WindowFactoryMock : public ImLogDetective::IWindowFactory 
{
public:
    MOCK_METHOD(std::unique_ptr<ImLogDetective::IScopedImGuiWindow>, createWindow, ());
    MOCK_METHOD(std::unique_ptr<ImLogDetective::IScopedImGuiWindow>, createChildWindow, (
        const std::string&, 
        const ImVec2&,
        const ImVec2&));

};

}