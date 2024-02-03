#pragma once

#include <string>
#include <vector>

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

struct InputText{
    
};

class IModalPopupFactory
{
public:
    virtual ~IModalPopupFactory() = default;
    virtual void open(ImVec2 popupPosition, ImVec2 popupSize, const std::string& name) = 0;
    virtual void beginLayout(const std::string& name) = 0; 
    virtual bool createButtonGroup(std::vector<PopupButton>& buttons) = 0;
    virtual bool createInputTextBox(const std::string& label, std::string& input) = 0;
    virtual void endLayout() = 0;
    virtual void close() = 0;
};

}