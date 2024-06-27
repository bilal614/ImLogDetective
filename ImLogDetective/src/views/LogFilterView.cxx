#include "views/LogFilterView.h"
#include "ImLogDetectiveDefs.h"
#include "dearimgui/IImGuiTextFilterWrapper.h"
#include "dearimgui/IImGuiWidgetWrapper.h"

namespace ImLogDetective
{
struct LogFilterView::Impl
{
    Impl(
        IImGuiTextFilterWrapper& textFilterWrapper,
        IImGuiWidgetWrapper& imGuiWidgetWrapper);
    ~Impl() = default;

    bool debugBoxChecked;
    bool infoBoxChecked;
    bool warningBoxChecked;
    bool errorBoxChecked;
    IImGuiTextFilterWrapper& textFilterWrapper;
    IImGuiWidgetWrapper& imGuiWidgetWrapper; 
    
};

LogFilterView::Impl::Impl(
    IImGuiTextFilterWrapper& textFilterWrapper,
    IImGuiWidgetWrapper& imGuiWidgetWrapper) :
        debugBoxChecked{true},
        infoBoxChecked{true},
        warningBoxChecked{true},
        errorBoxChecked{true},
        textFilterWrapper{textFilterWrapper},
        imGuiWidgetWrapper{imGuiWidgetWrapper}
{
}

LogFilterView::LogFilterView(
    IImGuiTextFilterWrapper& textFilterWrapper, 
    IImGuiWidgetWrapper& imGuiWidgetWrapper) :
        p{std::make_unique<Impl>(textFilterWrapper, imGuiWidgetWrapper)}
{
}

LogFilterView::~LogFilterView() = default;

void LogFilterView::drawFilterCheckBoxes() const
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