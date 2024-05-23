#include "views/WidgetFactory.h"
#include "ImLogDetectiveDefs.h"
#include "dearimgui/IMainViewPort.h"
#include "dearimgui/IScopedImGuiWindow.h"
#include "dearimgui/IImGuiWidgetWrapper.h"
#include "dearimgui/ListTreeWidget.h"
#include "dearimgui/ScopedImGuiWindow.hpp"

#include <unordered_map>

#include <iostream>

namespace ImLogDetective
{

struct WidgetFactory::Impl
{
    Impl(IWidgetFactory& widgetFactory, 
        const IMainViewPort& mainViewPort,
        IImGuiWidgetWrapper& imGuiWidgetWrapper);
    ~Impl() = default;
    std::unique_ptr<IScopedImGuiWindow> addWindow();
    

    const IMainViewPort& mainViewPort;
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
    IWidgetFactory& parent;
    IImGuiWidgetWrapper& imGuiWidgetWrapper;
};

WidgetFactory::Impl::Impl(IWidgetFactory& widgetFactory, 
    const IMainViewPort& mainViewport, 
    IImGuiWidgetWrapper& imGuiWidgetWrapper) :
        parent{widgetFactory},
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

std::unique_ptr<IScopedImGuiWindow> WidgetFactory::Impl::addWindow()
{
    return std::make_unique<ScopedImGuiWindow>(
        parent,
        WindowDefs::ApplicationName, 
        mainViewPort.getAreaSize(), 
        mainViewPort.getViewportPosition(), 
        openCloseWidgetPresent.get(), 
        mainWindowFlags,
        WindowType::MainWindow);
}

void WidgetFactory::Impl::createPopupButton(const std::string& button, bool& clicked)
{
    clicked = imGuiWidgetWrapper.button(button);
}

void WidgetFactory::Impl::createInputTextBox(const std::string& label, std::string& input, float width)
{
    imGuiWidgetWrapper.pushItemWidth(width);
    imGuiWidgetWrapper.inputText(label, input.data(), width);
    imGuiWidgetWrapper.popItemWidth();
}

void WidgetFactory::Impl::createProtectedInputTextBox(const std::string& label, std::string& input, float width)
{
    imGuiWidgetWrapper.pushItemWidth(width);
    imGuiWidgetWrapper.inputPassword(label, input.data(), width);
    imGuiWidgetWrapper.popItemWidth();
}

void WidgetFactory::Impl::drawInputTexBoxesGroup(std::vector<PopupInputTextBox>& inputTextBoxes, bool horizontal)
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

WidgetFactory::WidgetFactory(const IMainViewPort& mainViewport, IImGuiWidgetWrapper& imGuiWidgetWrapper) :
    p{std::make_unique<Impl>(*this, mainViewport, imGuiWidgetWrapper)}
{
}

WidgetFactory::~WidgetFactory() = default;

std::unique_ptr<IScopedImGuiWindow> WidgetFactory::createWindow()
{
    return p->addWindow();
}

std::unique_ptr<IScopedImGuiWindow> WidgetFactory::createChildWindow(
    const std::string& windowName,
    const ImVec2& position,
    const ImVec2& size)
{
    return std::make_unique<ScopedImGuiWindow>(
        p->parent,
        windowName, 
        size, 
        position, 
        p->openCloseWidgetPresent.get(),
        p->childWindowFlags,
        WindowType::ChildWindow
    );
}

void WidgetFactory::createUnformattedText(const std::string& text)
{
    p->imGuiWidgetWrapper.textUnformatted(text);
}

void WidgetFactory::createTextColored(std::string_view text, const TextColor& color)
{
    auto textColor = p->colorMap.find(color);
    if(textColor != p->colorMap.end())
    {
        p->imGuiWidgetWrapper.textColored(textColor->second, text.data());
    }
}

bool WidgetFactory::createSelectedTextColored(std::string_view text, const TextColor& color, bool selected)
{
    auto textColor = p->colorMap.find(color);
    if(textColor != p->colorMap.end())
    {
        return p->imGuiWidgetWrapper.selectableText(textColor->second, text.data(), selected);
    }
    return false;
}

std::unique_ptr<IListTreeWidget> WidgetFactory::createListTreeWidget()
{
    return std::make_unique<ListTreeWidget>();
}

void WidgetFactory::onSameLine()
{
    p->imGuiWidgetWrapper.sameLine();
}

void WidgetFactory::open(ImVec2 popupPosition, ImVec2 popupSize, const std::string& name)
{
    p->imGuiWidgetWrapper.openPopup(name);
    p->imGuiWidgetWrapper.setNextWindowPos(popupPosition);
    p->imGuiWidgetWrapper.setNextWindowSize(popupSize);
    p->modalPopupWindowOpened = true;
}

void WidgetFactory::beginLayout(const std::string& name)
{
    p->currentPopUp = name;
    p->modalPopupLayout[p->currentPopUp] = p->imGuiWidgetWrapper.beginPopupModal(p->currentPopUp);
}

bool WidgetFactory::createButton(PopupButton& button)
{
    if(p->modalPopupLayout[p->currentPopUp])
    {
        p->createPopupButton(button.name, button.clicked);
        return true;
    }
    std::cerr << "Missing call to beginLayout" << std::endl;
    return false;
}

bool WidgetFactory::createButtonGroup(std::vector<PopupButton>& buttons)
{
    if(p->modalPopupLayout[p->currentPopUp])
    {
        for(auto it = buttons.begin(); it != buttons.end(); ++it)
        {
            p->createPopupButton(it->name, it->clicked);
            if(it  != --buttons.end())
            {
                onSameLine();
            }
        }
        return true;
    }
    std::cerr << "Missing call to beginLayout" << std::endl;
    return false;
}

bool WidgetFactory::createInputTextBox(const std::string& label, std::string& input, float width)
{
    if(p->modalPopupLayout[p->currentPopUp])
    {
        p->createInputTextBox(label, input, width);
        return true;
    }
    std::cerr << "Missing call to beginLayout" << std::endl;
    return false;
}

bool WidgetFactory::createProtectedInputTextBox(const std::string& label, std::string& input, float width)
{
    if(p->modalPopupLayout[p->currentPopUp])
    {
        p->createProtectedInputTextBox(label, input, width);
        return true;
    }
    std::cerr << "Missing call to beginLayout" << std::endl;
    return false;
}

bool WidgetFactory::createInputTextBoxGroup(
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

bool WidgetFactory::showErrorText(const std::string& errorMessage)
{
    if(p->modalPopupLayout[p->currentPopUp])
    {
        p->imGuiWidgetWrapper.textColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), errorMessage);
        return true;
    }
    return false;
}

void WidgetFactory::endLayout()
{
    if(p->modalPopupLayout[p->currentPopUp])
    {
        p->imGuiWidgetWrapper.endPopup();
        p->modalPopupLayout[p->currentPopUp] = false;
    }
}

void WidgetFactory::close()
{
    p->imGuiWidgetWrapper.closeCurrentPopup();
    p->currentPopUp = std::string{};
    p->modalPopupWindowOpened = false;
}

bool WidgetFactory::isPopupOpen()
{
    return p->modalPopupWindowOpened;
}

}