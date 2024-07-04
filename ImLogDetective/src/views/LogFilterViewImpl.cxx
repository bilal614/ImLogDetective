#include "views/LogFilterViewImpl.h"
#include "ImLogDetectiveDefs.h"
#include "dearimgui/ImGuiTextFilterWrapper.h"
#include "dearimgui/ImGuiWidgetWrapper.h"

namespace ImLogDetective
{
struct LogFilterViewImpl::Impl
{
    Impl(
        ImGuiTextFilterWrapper& textFilterWrapper,
        ImGuiWidgetWrapper& imGuiWidgetWrapper);
    ~Impl() = default;

    bool debugBoxChecked;
    bool infoBoxChecked;
    bool warningBoxChecked;
    bool errorBoxChecked;
    ImGuiTextFilterWrapper& textFilterWrapper;
    ImGuiWidgetWrapper& imGuiWidgetWrapper; 
    
};

LogFilterViewImpl::Impl::Impl(
    ImGuiTextFilterWrapper& textFilterWrapper,
    ImGuiWidgetWrapper& imGuiWidgetWrapper) :
        debugBoxChecked{true},
        infoBoxChecked{true},
        warningBoxChecked{true},
        errorBoxChecked{true},
        textFilterWrapper{textFilterWrapper},
        imGuiWidgetWrapper{imGuiWidgetWrapper}
{
}

LogFilterViewImpl::LogFilterViewImpl(
    ImGuiTextFilterWrapper& textFilterWrapper, 
    ImGuiWidgetWrapper& imGuiWidgetWrapper) :
        p{std::make_unique<Impl>(textFilterWrapper, imGuiWidgetWrapper)}
{
}

LogFilterViewImpl::~LogFilterViewImpl() = default;

void LogFilterViewImpl::drawFilterCheckBoxes() const
{
    p->imGuiWidgetWrapper.sameLine();
    p->imGuiWidgetWrapper.checkBox(LogFilterDefs::DebugCheckBoxLabel, p->debugBoxChecked);
    p->imGuiWidgetWrapper.sameLine();
    p->imGuiWidgetWrapper.checkBox(LogFilterDefs::InfoCheckBoxLabel, p->infoBoxChecked);
    p->imGuiWidgetWrapper.sameLine();
    p->imGuiWidgetWrapper.checkBox(LogFilterDefs::WarningCheckBoxLabel, p->warningBoxChecked);
    p->imGuiWidgetWrapper.sameLine();
    p->imGuiWidgetWrapper.checkBox(LogFilterDefs::ErrorCheckBoxLabel, p->errorBoxChecked);
    p->imGuiWidgetWrapper.separator();
    p->textFilterWrapper.draw();
}

bool LogFilterViewImpl::getDebugChecked() const
{
    return p->debugBoxChecked;
}

bool LogFilterViewImpl::getInfoChecked() const
{
    return p->infoBoxChecked;
}

bool LogFilterViewImpl::getWarningChecked() const
{
    return p->warningBoxChecked;
}

bool LogFilterViewImpl::getErrorChecked() const
{
    return p->errorBoxChecked;
} 

}