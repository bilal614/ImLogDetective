
#ifndef IMLOGDETECTIVE_DEARIMGUI_IMGUIWIDGETWRAPPER_H
#define IMLOGDETECTIVE_DEARIMGUI_IMGUIWIDGETWRAPPER_H

#include <string>

struct ImVec2;
struct ImVec4;

namespace ImLogDetective
{

class ImGuiWidgetWrapper
{
public:
    virtual ~ImGuiWidgetWrapper() = default;
    virtual bool beginPopupModal(const std::string& name) = 0;
    virtual bool button(const std::string& label) = 0;
    virtual bool checkBox(std::string_view label, bool& checked) = 0;
    virtual void closeCurrentPopup() = 0;
    virtual bool collapsingHeader(const std::string& title) = 0;
    virtual void endPopup() = 0;
    virtual bool inputText(const std::string& label, char* buf, size_t boxLength) = 0;
    virtual bool inputPassword(const std::string& label, char* buf, size_t boxLength) = 0;
    virtual void openPopup(const std::string& name) = 0;
    virtual void popItemWidth() = 0;
    virtual void pushItemWidth(float width) = 0;
    virtual void sameLine() = 0;
    virtual void separator() = 0;
    virtual void setNextWindowPos(const ImVec2& pos) = 0;
    virtual void setNextWindowSize(const ImVec2& size) = 0;
    virtual void textColored(const ImVec4& color, std::string_view text) = 0;
    virtual void textUnformatted(std::string_view text) = 0;
    virtual bool selectableText(const ImVec4& color, std::string_view text, bool selected) = 0;
};

}

#endif