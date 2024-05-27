#pragma once
#include "IImGuiWidgetWrapper.h"
#include <string>

namespace ImLogDetective
{

class ImGuiWidgetWrapper : public IImGuiWidgetWrapper
{
public:
    bool beginPopupModal(const std::string& name) final;
    bool button(const std::string& label) final;
    void closeCurrentPopup() final;
    bool collapsingHeader(const std::string& title) final;
    void endPopup() final;
    bool inputText(const std::string& label, char* buf, size_t boxLength) final;
    bool inputPassword(const std::string& label, char* buf, size_t boxLength) final;
    void openPopup(const std::string& name) final;
    void popItemWidth() final;
    void pushItemWidth(float width) final;
    void sameLine() final;
    void setNextWindowPos(const ImVec2& pos) final;
    void setNextWindowSize(const ImVec2& size) final;
    void textColored(const ImVec4& color, const std::string& text) final;
    void textUnformatted(const std::string& text) final;
    bool selectableText(const ImVec4& color, const std::string& text, bool selected) final;
};

}