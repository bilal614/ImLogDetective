
#ifndef IMLOGDETECTIVE_DEARIMGUI_MAINVIEWPORTIMPL_H
#define IMLOGDETECTIVE_DEARIMGUI_MAINVIEWPORTIMPL_H

#include "dearimgui/MainViewPort.h"
#include <memory>

namespace ImLogDetective
{
class IOContext;

class MainViewPortImpl : public MainViewPort 
{
public:
    MainViewPortImpl(IOContext& ioContext);
    ~MainViewPortImpl();
    ImVec2 getAreaSize() const override;
    ImVec2 getWorkAreaSize() const override;
    ImVec2 getViewportPosition() const override;
    ImVec2 getViewportCenter() const override;
    void setViewportScale(const float scaleFactor) override;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}

#endif