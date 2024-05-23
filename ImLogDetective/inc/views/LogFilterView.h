#pragma once
#include "views/ILogFilterView.h"

#include <memory>

namespace ImLogDetective
{

class IImGuiTextFilterWrapper;

class LogFilterView : public ILogFilterView
{
public:
    LogFilterView(IImGuiTextFilterWrapper& textFilterWrapper);
    ~LogFilterView();
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