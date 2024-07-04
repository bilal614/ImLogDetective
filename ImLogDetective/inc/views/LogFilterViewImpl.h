
#ifndef IMLOGDETECTIVE_VIEWS_LOGFILTERVIEWIMPL_H
#define IMLOGDETECTIVE_VIEWS_LOGFILTERVIEWIMPL_H

#include "views/LogFilterView.h"
#include <memory>

namespace ImLogDetective
{

class IImGuiTextFilterWrapper;
class IImGuiWidgetWrapper;

class LogFilterViewImpl : public LogFilterView
{
public:
    LogFilterViewImpl(
        IImGuiTextFilterWrapper& textFilterWrapper, 
        IImGuiWidgetWrapper& imGuiWidgetWrapper);
    ~LogFilterViewImpl();
    void drawFilterCheckBoxes() const override;
    bool getDebugChecked() const override;
    bool getInfoChecked() const override;
    bool getWarningChecked() const override;
    bool getErrorChecked() const override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}

#endif