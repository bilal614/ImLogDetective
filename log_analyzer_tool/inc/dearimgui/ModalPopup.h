#pragma once

#include "IModalPopup.h"
#include <string>

namespace LogAnalyzerTool
{

class ModalPopup : public IModalPopup
{
public:
    void open(ImVec2 popupPosition, ImVec2 popupSize, const std::string& name) override;
    void close() override;
private:

};

}