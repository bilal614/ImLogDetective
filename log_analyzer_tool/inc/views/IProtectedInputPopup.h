#pragma once

#include <string>
#include "views/IPopup.h"

struct ImVec2;

namespace LogAnalyzerTool
{

class IProtectedInputPopup : public IPopup<std::string>
{
};

}