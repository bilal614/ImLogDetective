
#ifndef IMLOGDETECTIVE_DEARIMGUI_IMGUIWIDGETWRAPPERIMPL_H
#define IMLOGDETECTIVE_DEARIMGUI_IMGUIWIDGETWRAPPERIMPL_H

#include "dearimgui/ImGuiWidgetWrapper.h"

namespace ImLogDetective
{

class ImGuiWidgetWrapperImpl : public ImGuiWidgetWrapper
{
public:
    bool beginPopupModal(const std::string& name) final;
    bool button(const std::string& label) final;
    bool checkBox(std::string_view label, bool& checked) final;
    void closeCurrentPopup() final;
    bool collapsingHeader(const std::string& title) final;
    void endPopup() final;
    bool inputText(const std::string& label, char* buf, size_t boxLength) final;
    bool inputPassword(const std::string& label, char* buf, size_t boxLength) final;
    void openPopup(const std::string& name) final;
    void popItemWidth() final;
    void pushItemWidth(float width) final;
    void sameLine() final;
    void separator() final;
    void setNextWindowPos(const ImVec2& pos) final;
    void setNextWindowSize(const ImVec2& size) final;
    void textColored(const ImVec4& color, std::string_view text) final;
    void textUnformatted(std::string_view text) final;
    bool selectableText(const ImVec4& color, std::string_view text, bool selected) final;
    void setNextWindowPosAndSize(const ImVec2& pos, const ImVec2& size) final;
    void windowBegin(const std::string& windowName, bool* openClose, ImGuiWindowFlags flags) final;
    void windowEnd() final;
    void childWindowBegin(const std::string& windowName, const ImVec2& size, ImGuiWindowFlags flags) final;
    void childWindowEnd() final;
};

}

#endif