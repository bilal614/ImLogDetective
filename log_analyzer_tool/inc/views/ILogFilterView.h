#pragma once

namespace LogAnalyzerTool
{

class ILogFilterView
{
public:
    virtual ~ILogFilterView() = default;
    virtual void drawFilterCheckBoxes() const = 0;
    virtual bool getDebugChecked() const = 0;
    virtual bool getInfoChecked() const = 0;
    virtual bool getWarningChecked() const = 0;
    virtual bool getErrorChecked() const = 0; 
};

}