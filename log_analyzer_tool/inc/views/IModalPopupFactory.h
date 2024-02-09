#pragma once

#include <string>
#include <vector>

struct ImVec2;

namespace LogAnalyzerTool
{

struct PopupButton {
    PopupButton(const std::string name) : 
        name{name},
        clicked{false}
    {} 
    std::string name;
    bool clicked;
};

struct PopupInputTextBox {
    PopupInputTextBox(const std::string name, float width = 200) : 
        name{name},
        width{width},
        input{}
    {} 
    std::string name;
    float width;
    std::string input;
};

class IModalPopupFactory
{
public:
    virtual ~IModalPopupFactory() = default;
    virtual void open(ImVec2 popupPosition, ImVec2 popupSize, const std::string& name) = 0;
    virtual void beginLayout(const std::string& name) = 0; 
    virtual bool createButtonGroup(std::vector<PopupButton>& buttons) = 0;
    virtual bool createInputTextBox(const std::string& label, std::string& input, float width) = 0;
    virtual bool createInputTextBoxGroup(
        std::vector<PopupInputTextBox>& inputTextBoxes, 
        const std::string& title,
        bool horizontal,
        bool collapsable=false) = 0;
    virtual bool showErrorText(const std::string& errorMessage) = 0;
    virtual void endLayout() = 0;
    virtual void close() = 0;
    virtual bool isPopupOpen() = 0;
};

}