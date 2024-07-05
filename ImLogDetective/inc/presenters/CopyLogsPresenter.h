
#ifndef IMLOGDETECTIVE_PRESENTERS_COPYLOGSPRESENTER_H
#define IMLOGDETECTIVE_PRESENTERS_COPYLOGSPRESENTER_H

struct ImVec2;

namespace ImLogDetective
{

class CopyLogsPresenter
{
public:
    virtual ~CopyLogsPresenter() = default;
    virtual void update(bool openPopup, const ImVec2& popupPosition, const ImVec2& popupSize) = 0;
    virtual void monitorCopyLogs() = 0;
    virtual bool isClosed() = 0;
};

}

#endif