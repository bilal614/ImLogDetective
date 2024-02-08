#include "dearimgui/IMainViewPort.h"
#include "LogAnalyzerToolDefs.h"
#include "dearimgui/IScopedImGuiWindow.h"
#include "dearimgui/ListTreeWidget.h"
#include "dearimgui/ScopedImGuiWindow.hpp"
#include "dearimgui/WidgetFactory.h"
#include "imgui.h"

#include <unordered_map>

#include <iostream>

namespace LogAnalyzerTool
{

struct WidgetFactory::Impl
{
    Impl(IWidgetFactory& widgetFactory, const IMainViewPort& mainViewPort);
    ~Impl() = default;
    std::unique_ptr<IScopedImGuiWindow> addWindow();
    

    const IMainViewPort& mainViewPort;
    std::unique_ptr<bool> openCloseWidgetPresent;
    ImGuiWindowFlags mainWindowFlags;
    ImGuiWindowFlags childWindowFlags;

    //ModalPopup state
    bool modalPopupWindowOpened;
    bool modalPopupLayout;
    void createPopupButton(const std::string& button, bool& clicked);
    void createInputTextBox(const std::string& label, std::string& input, float width);
    void drawInputTexBoxesGroup(std::vector<PopupInputTextBox>& inputTextBoxes, bool horizontal = true);

    std::unordered_map<TextColor, ImVec4> colorMap;
    IWidgetFactory& parent;
};

WidgetFactory::Impl::Impl(IWidgetFactory& widgetFactory, const IMainViewPort& mainWindow) :
    parent{widgetFactory},
    mainViewPort{mainWindow},
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
        WindowDefs::LogAnalyzerToolApplicationName, 
        mainViewPort.getAreaSize(), 
        mainViewPort.getViewportPosition(), 
        openCloseWidgetPresent.get(), 
        mainWindowFlags,
        WindowType::MainWindow);
}

void WidgetFactory::Impl::createPopupButton(const std::string& button, bool& clicked)
{
    clicked = ImGui::Button(button.c_str());
}

void WidgetFactory::Impl::createInputTextBox(const std::string& label, std::string& input, float width)
{
    ImGui::PushItemWidth(width);
    ImGui::InputText(label.c_str(), input.data(), Bounds::MaxTextboxInputLength);
    ImGui::PopItemWidth();
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
            ImGui::SameLine();
        }
    }
}

WidgetFactory::WidgetFactory(const IMainViewPort& mainWindow) :
    p{std::make_unique<Impl>(*this, mainWindow)}
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
    ImGui::TextUnformatted(text.c_str());
}

void WidgetFactory::createTextColored(std::string_view text, const TextColor& color)
{
    auto textColor = p->colorMap.find(color);
    if(textColor != p->colorMap.end())
    {
        ImGui::TextColored(textColor->second, "%s", text.data());
    }
}

std::unique_ptr<IListTreeWidget> WidgetFactory::createListTreeWidget()
{
    return std::make_unique<ListTreeWidget>();
}

void WidgetFactory::onSameLine()
{
    ImGui::SameLine();
}

void WidgetFactory::open(ImVec2 popupPosition, ImVec2 popupSize, const std::string& name)
{
    ImGui::OpenPopup(name.c_str());
    ImGui::SetNextWindowPos(popupPosition, ImGuiCond_Appearing, ImVec2(0.5f, 0.25f));
    ImGui::SetNextWindowSize(popupSize, ImGuiCond_Appearing);
    p->modalPopupWindowOpened = true;
}

void WidgetFactory::beginLayout(const std::string& name)
{
    p->modalPopupLayout = ImGui::BeginPopupModal(name.c_str(), NULL, ImGuiWindowFlags_NoDecoration);
}

bool WidgetFactory::createButtonGroup(std::vector<PopupButton>& buttons)
{
    if(p->modalPopupLayout)
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
    if(p->modalPopupLayout)
    {
        p->createInputTextBox(label, input, width);
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
    if(p->modalPopupLayout)
    {
        if(collapsable)
        {
            if (ImGui::CollapsingHeader(title.c_str(), ImGuiTreeNodeFlags_None))
            {
                p->drawInputTexBoxesGroup(inputTextBoxes, horizontal);
            }
            return true;
        }
        ImGui::TextUnformatted(title.c_str());
        p->drawInputTexBoxesGroup(inputTextBoxes, horizontal);
        return true;
    }
    std::cerr << "Missing call to beginLayout" << std::endl;
    return false;
}

bool WidgetFactory::showErrorText(const std::string& errorMessage)
{
    if(p->modalPopupLayout)
    {
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "%s", errorMessage.c_str());
        return true;
    }
    return false;
}

void WidgetFactory::endLayout()
{
    if(p->modalPopupLayout)
    {
        ImGui::EndPopup();
        p->modalPopupLayout = false;
    }
}

void WidgetFactory::close()
{
    ImGui::CloseCurrentPopup();
    p->modalPopupWindowOpened = false;
}

bool WidgetFactory::isPopupOpen()
{
    return p->modalPopupWindowOpened;
}

}