
#ifndef IMLOGDETECTIVE_VIEWS_WIDGETFACTORYIMPL_H
#define IMLOGDETECTIVE_VIEWS_WIDGETFACTORYIMPL_H

#include "dearimgui/MainViewPort.h"
#include "views/WidgetFactory.h"
#include <memory>
#include <string>


namespace ImLogDetective
{
class MainViewPort;
class ImGuiWidgetWrapper;
class ScopedImGuiWindow;

class WidgetFactoryImpl : public WidgetFactory
{
public:
    WidgetFactoryImpl(const MainViewPort& mainViewport, ImGuiWidgetWrapper& imGuiWidgetWrapper);
    ~WidgetFactoryImpl();
    // Window creation specific functions
    std::unique_ptr<ScopedImGuiWindow> createWindow() override;
    std::unique_ptr<ScopedImGuiWindow> createChildWindow(
        const std::string& windowName, 
        const ImVec2& position,
        const ImVec2& size) override;

    // Text creation functions
    void createUnformattedText(const std::string& text) override;
    void createTextColored(std::string_view text, const TextColor& color) override;
    bool createSelectedTextColored(std::string_view text, const TextColor& color, bool selected) override;

    //List tree widget
    std::unique_ptr<ListTreeWidget> createListTreeWidget() override;

    //ModalPopup widgets
    void open(ImVec2 popupPosition, ImVec2 popupSize, const std::string& name) override;
    void beginLayout(const std::string& name) override;
    bool createButton(PopupButton& button) override;
    bool createButtonGroup(std::vector<PopupButton>& buttons) override;
    bool createInputTextBox(const std::string& label, std::string& input, float width) override;
    bool createProtectedInputTextBox(const std::string& label, std::string& input, float width) override;
    bool createInputTextBoxGroup(std::vector<PopupInputTextBox>& inputTextBoxes,
        const std::string& title, 
        bool horizontal,
        bool collapsable) override;
    bool showErrorText(const std::string& errorMessage) override;
    void endLayout() override;
    void close() override;
    bool isPopupOpen() override;

private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}

#endif