#include "views/WidgetFactoryImpl.h"
#include "ImLogDetectiveDefs.h"
#include "dearimgui/MainViewPort.h"
#include "dearimgui/ScopedImGuiWindow.h"
#include "dearimgui/ImGuiWidgetWrapper.h"
#include "dearimgui/ListTreeWidgetImpl.h"
#include "dearimgui/ScopedImGuiWindowImpl.hpp"
#include "dearimgui/TextColor.h"
#include <unordered_map>
#include <iostream>

namespace ImLogDetective
{

struct WidgetFactoryImpl::Impl
{
    Impl(const MainViewPort& mainViewPort,
        ImGuiWidgetWrapper& imGuiWidgetWrapper);
    ~Impl() = default;
    std::unique_ptr<ScopedImGuiWindow> addWindow();
    

    const MainViewPort& mainViewPort;
    std::unique_ptr<bool> openCloseWidgetPresent;
    ImGuiWindowFlags mainWindowFlags;
    ImGuiWindowFlags childWindowFlags;

    //ModalPopup state
    bool modalPopupWindowOpened;
    std::unordered_map<std::string, bool>  modalPopupLayout;
    std::string currentPopUp;
    void createPopupButton(const std::string& button, bool& clicked);
    void createInputTextBox(const std::string& label, std::string& input, float width);
    void createProtectedInputTextBox(const std::string& label, std::string& input, float width);
    void drawInputTexBoxesGroup(std::vector<PopupInputTextBox>& inputTextBoxes, bool horizontal = true);

    std::unordered_map<TextColor, ImVec4> colorMap;
    ImGuiWidgetWrapper& imGuiWidgetWrapper;
};

WidgetFactoryImpl::Impl::Impl(const MainViewPort& mainViewport, 
    ImGuiWidgetWrapper& imGuiWidgetWrapper) :
        imGuiWidgetWrapper{imGuiWidgetWrapper},
        mainViewPort{mainViewport},
        openCloseWidgetPresent{nullptr},
        mainWindowFlags{0},
        childWindowFlags{0},
        colorMap{
            {TextColor::Red, ImVec4(1.0f, 0.0f, 0.0f, 1.0f)},
            {TextColor::Orange, ImVec4(1.0f, 0.5f, 0.0f, 1.0f)},
            {TextColor::Yellow, ImVec4(1.0f, 1.0f, 0.0f, 1.0f)},
            {TextColor::Green, ImVec4(0.0f, 1.0f, 0.0f, 1.0f)},
            {TextColor::White, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)},
        }
{
    mainWindowFlags = ImGuiWindowFlags_MenuBar |
                ImGuiWindowFlags_NoMove | 
                ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoCollapse;
    childWindowFlags = ImGuiWindowFlags_HorizontalScrollbar;
}

std::unique_ptr<ScopedImGuiWindow> WidgetFactoryImpl::Impl::addWindow()
{
    return std::make_unique<ScopedImGuiWindowImpl<WindowType::MainWindow>>(
        imGuiWidgetWrapper,
        WindowDefs::ApplicationName, 
        mainViewPort.getAreaSize(), 
        mainViewPort.getViewportPosition(), 
        openCloseWidgetPresent.get(), 
        mainWindowFlags);
}

void WidgetFactoryImpl::Impl::createPopupButton(const std::string& button, bool& clicked)
{
    clicked = imGuiWidgetWrapper.button(button);
}

void WidgetFactoryImpl::Impl::createInputTextBox(const std::string& label, std::string& input, float width)
{
    imGuiWidgetWrapper.pushItemWidth(width);
    imGuiWidgetWrapper.inputText(label, input.data(), width);
    imGuiWidgetWrapper.popItemWidth();
}

void WidgetFactoryImpl::Impl::createProtectedInputTextBox(const std::string& label, std::string& input, float width)
{
    imGuiWidgetWrapper.pushItemWidth(width);
    imGuiWidgetWrapper.inputPassword(label, input.data(), width);
    imGuiWidgetWrapper.popItemWidth();
}

void WidgetFactoryImpl::Impl::drawInputTexBoxesGroup(std::vector<PopupInputTextBox>& inputTextBoxes, bool horizontal)
{
    for(auto it = inputTextBoxes.begin(); it != inputTextBoxes.end(); ++it)
    {
        createInputTextBox(it->name, it->input, it->width);
        if(!horizontal)
        {
            continue;
        }
        if(it  != --inputTextBoxes.end())
        {
            imGuiWidgetWrapper.sameLine();
        }
    }
}

WidgetFactoryImpl::WidgetFactoryImpl(const MainViewPort& mainViewport, ImGuiWidgetWrapper& imGuiWidgetWrapper) :
    p{std::make_unique<Impl>(mainViewport, imGuiWidgetWrapper)}
{
}

WidgetFactoryImpl::~WidgetFactoryImpl() = default;

std::unique_ptr<ScopedImGuiWindow> WidgetFactoryImpl::createWindow()
{
    return p->addWindow();
}

std::unique_ptr<ScopedImGuiWindow> WidgetFactoryImpl::createChildWindow(
    const std::string& windowName,
    const ImVec2& position,
    const ImVec2& size)
{
    return std::make_unique<ScopedImGuiWindowImpl<WindowType::ChildWindow>>(
        p->imGuiWidgetWrapper,
        windowName, 
        size, 
        position, 
        p->openCloseWidgetPresent.get(),
        p->childWindowFlags
    );
}

void WidgetFactoryImpl::createUnformattedText(const std::string& text)
{
    p->imGuiWidgetWrapper.textUnformatted(text);
}

void WidgetFactoryImpl::createTextColored(std::string_view text, const TextColor& color)
{
    auto textColor = p->colorMap.find(color);
    if(textColor != p->colorMap.end())
    {
        p->imGuiWidgetWrapper.textColored(textColor->second, text.data());
    }
}

bool WidgetFactoryImpl::createSelectedTextColored(std::string_view text, const TextColor& color, bool selected)
{
    auto textColor = p->colorMap.find(color);
    if(textColor != p->colorMap.end())
    {
        if(color == TextColor::Yellow)
        {
            p->imGuiWidgetWrapper.textColored(textColor->second, text);
            return true;
        }
        return p->imGuiWidgetWrapper.selectableText(textColor->second, text.data(), selected);
    }
    return false;
}

std::unique_ptr<ListTreeWidget> WidgetFactoryImpl::createListTreeWidget()
{
    return std::make_unique<ListTreeWidgetImpl>();
}

void WidgetFactoryImpl::open(ImVec2 popupPosition, ImVec2 popupSize, const std::string& name)
{
    p->imGuiWidgetWrapper.openPopup(name);
    p->imGuiWidgetWrapper.setNextWindowPos(popupPosition);
    p->imGuiWidgetWrapper.setNextWindowSize(popupSize);
    p->modalPopupWindowOpened = true;
}

void WidgetFactoryImpl::beginLayout(const std::string& name)
{
    p->currentPopUp = name;
    p->modalPopupLayout[p->currentPopUp] = p->imGuiWidgetWrapper.beginPopupModal(p->currentPopUp);
}

bool WidgetFactoryImpl::createButton(PopupButton& button)
{
    if(p->modalPopupLayout[p->currentPopUp])
    {
        p->createPopupButton(button.name, button.clicked);
        return true;
    }
    std::cerr << "Missing call to beginLayout" << std::endl;
    return false;
}

bool WidgetFactoryImpl::createButtonGroup(std::vector<PopupButton>& buttons)
{
    if(p->modalPopupLayout[p->currentPopUp])
    {
        for(auto it = buttons.begin(); it != buttons.end(); ++it)
        {
            p->createPopupButton(it->name, it->clicked);
            if(it  != --buttons.end())
            {
                p->imGuiWidgetWrapper.sameLine();
            }
        }
        return true;
    }
    std::cerr << "Missing call to beginLayout" << std::endl;
    return false;
}

bool WidgetFactoryImpl::createInputTextBox(const std::string& label, std::string& input, float width)
{
    if(p->modalPopupLayout[p->currentPopUp])
    {
        p->createInputTextBox(label, input, width);
        return true;
    }
    std::cerr << "Missing call to beginLayout" << std::endl;
    return false;
}

bool WidgetFactoryImpl::createProtectedInputTextBox(const std::string& label, std::string& input, float width)
{
    if(p->modalPopupLayout[p->currentPopUp])
    {
        p->createProtectedInputTextBox(label, input, width);
        return true;
    }
    std::cerr << "Missing call to beginLayout" << std::endl;
    return false;
}

bool WidgetFactoryImpl::createInputTextBoxGroup(
    std::vector<PopupInputTextBox>& inputTextBoxes,
    const std::string& title, 
    bool horizontal,
    bool collapsable)
{
    if(p->modalPopupLayout[p->currentPopUp])
    {
        if(collapsable)
        {
            if (p->imGuiWidgetWrapper.collapsingHeader(title))
            {
                p->drawInputTexBoxesGroup(inputTextBoxes, horizontal);
            }
            return true;
        }
        p->imGuiWidgetWrapper.textUnformatted(title);
        p->drawInputTexBoxesGroup(inputTextBoxes, horizontal);
        return true;
    }
    std::cerr << "Missing call to beginLayout" << std::endl;
    return false;
}

bool WidgetFactoryImpl::showErrorText(const std::string& errorMessage)
{
    if(p->modalPopupLayout[p->currentPopUp])
    {
        p->imGuiWidgetWrapper.textColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), errorMessage);
        return true;
    }
    return false;
}

void WidgetFactoryImpl::endLayout()
{
    if(p->modalPopupLayout[p->currentPopUp])
    {
        p->imGuiWidgetWrapper.endPopup();
        p->modalPopupLayout[p->currentPopUp] = false;
    }
}

void WidgetFactoryImpl::close()
{
    p->imGuiWidgetWrapper.closeCurrentPopup();
    p->currentPopUp = std::string{};
    p->modalPopupWindowOpened = false;
}

bool WidgetFactoryImpl::isPopupOpen()
{
    return p->modalPopupWindowOpened;
}

}