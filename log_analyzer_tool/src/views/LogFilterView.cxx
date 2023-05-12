#include "views/LogFilterView.h"
#include "imgui.h"

namespace LogAnalyzerTool
{
struct LogFilterView::Impl
{
    Impl();
    ~Impl() = default;

    bool debugBoxChecked;
    bool infoBoxChecked;
    bool warningBoxChecked;
    bool errorBoxChecked;
};

LogFilterView::Impl::Impl() :
    debugBoxChecked{true},
    infoBoxChecked{true},
    warningBoxChecked{true},
    errorBoxChecked{true}
{

}

LogFilterView::LogFilterView() :
    p{std::make_unique<Impl>()}
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