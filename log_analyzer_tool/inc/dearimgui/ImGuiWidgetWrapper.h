#pragma once
#include "IImGuiWidgetWrapper.h"
#include <string>

namespace LogAnalyzerTool
{

class ImGuiWidgetWrapper : public IImGuiWidgetWrapper
{
public:
    bool beginPopupModal(const std::string& name);
    bool button(const std::string& label);
    void closeCurrentPopup() ;
    bool collapsingHeader(const std::string& title);
    void endPopup();
    bool inputText(const std::string& label, char* buf, size_t boxLength);
    bool inputPassword(const std::string& label, char* buf, size_t boxLength);
    void openPopup(const std::string& name);
    void popItemWidth();
    void pushItemWidth(float width);
    void sameLine();
    void setNextWindowPos(const ImVec2& pos);
    void setNextWindowSize(const ImVec2& size);
    void textColored(const ImVec4& color, const std::string& text);
    void textUnformatted(const std::string& text);
};

}