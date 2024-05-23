#include "views/LogFilterView.h"
#include "dearimgui/IImGuiTextFilterWrapper.h"
#include "imgui.h"

namespace ImLogDetective
{
struct LogFilterView::Impl
{
    Impl(IImGuiTextFilterWrapper& textFilterWrapper);
    ~Impl() = default;

    bool debugBoxChecked;
    bool infoBoxChecked;
    bool warningBoxChecked;
    bool errorBoxChecked;
    IImGuiTextFilterWrapper& textFilterWrapper;
    
};

LogFilterView::Impl::Impl(IImGuiTextFilterWrapper& textFilterWrapper) :
    debugBoxChecked{true},
    infoBoxChecked{true},
    warningBoxChecked{true},
    errorBoxChecked{true},
    textFilterWrapper{textFilterWrapper}
{
}

LogFilterView::LogFilterView(IImGuiTextFilterWrapper& textFilterWrapper) :
    p{std::make_unique<Impl>(textFilterWrapper)}
{
}

LogFilterView::~LogFilterView() = default;

void LogFilterView::drawFilterCheckBoxes() const
{
    ImGui::SameLine();
    ImGui::Checkbox("DEBUG", &p->debugBoxChecked);
    ImGui::SameLine();
    ImGui::Checkbox("INFO", &p->infoBoxChecked);
    ImGui::SameLine();
    ImGui::Checkbox("WARNING", &p->warningBoxChecked);
    ImGui::SameLine();
    ImGui::Checkbox("ERROR", &p->errorBoxChecked);
    ImGui::Separator();
    p->textFilterWrapper.draw();
}

bool LogFilterView::getDebugChecked() const
{
    return p->debugBoxChecked;
}

bool LogFilterView::getInfoChecked() const
{
    return p->infoBoxChecked;
}

bool LogFilterView::getWarningChecked() const
{
    return p->warningBoxChecked;
}

bool LogFilterView::getErrorChecked() const
{
    return p->errorBoxChecked;
} 

}