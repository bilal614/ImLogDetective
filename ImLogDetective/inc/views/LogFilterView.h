
#ifndef IMLOGDETECTIVE_VIEWS_LOGFILTERVIEW_H
#define IMLOGDETECTIVE_VIEWS_LOGFILTERVIEW_H

namespace ImLogDetective
{

class LogFilterView
{
public:
    virtual ~LogFilterView() = default;
    virtual void drawFilterCheckBoxes() const = 0;
    virtual bool getDebugChecked() const = 0;
    virtual bool getInfoChecked() const = 0;
    virtual bool getWarningChecked() const = 0;
    virtual bool getErrorChecked() const = 0; 
};

}

#endif