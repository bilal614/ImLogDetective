#pragma once

#include "IProtectedInputPopup.h"
#include <memory>
#include <string>

struct ImVec2;

namespace LogAnalyzerTool
{

class IModalPopupFactory;

class ProtectedInputPopup : public IProtectedInputPopup
{
public:
    ProtectedInputPopup(IModalPopupFactory& modalPopupFactory);
    ~ProtectedInputPopup();
    void open(const ImVec2& popupPosition, const ImVec2& popupSize) final;
    void draw() final;
    void close() final;
    bool isOpen() final;
    bool okBtnClicked() final;
    bool closeBtnClicked() final;
    std::string getInput() final;
private:
    struct Impl;
    std::unique_ptr<Impl> p;

};

}