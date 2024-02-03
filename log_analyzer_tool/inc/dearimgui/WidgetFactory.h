#pragma once

#include "dearimgui/IMainViewPort.h"
#include "dearimgui/IWidgetFactory.h"
#include <memory>
#include <string>


namespace LogAnalyzerTool
{
class IMainViewPort;

class WidgetFactory : public IWidgetFactory
{
public:
    WidgetFactory(const IMainViewPort& mainWindow);
    ~WidgetFactory();
    // Window creation specific functions
    std::unique_ptr<IScopedImGuiWindow> createWindow() override;
    std::unique_ptr<IScopedImGuiWindow> createChildWindow(
        const std::string& windowName, 
        const ImVec2& position,
        const ImVec2& size) override;

    // Text creation functions
    void createUnformattedText(const std::string& text) override;
    void createTextColored(std::string_view text, const TextColor& color) override;

    //List tree widget
    std::unique_ptr<IListTreeWidget> createListTreeWidget() override;

    //Layout manipulation
    void onSameLine() override;

    //ModalPopup widgets
    void open(ImVec2 popupPosition, ImVec2 popupSize, const std::string& name) override;
    void beginLayout(const std::string& name) override;
    bool createButtonGroup(std::vector<PopupButton>& buttons) override;
    bool createInputTextBox(const std::string& label, std::string& input) override;
    void endLayout() override;
    void close() override;

private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}