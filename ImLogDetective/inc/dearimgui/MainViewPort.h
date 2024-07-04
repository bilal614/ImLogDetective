
#ifndef IMLOGDETECTIVE_DEARIMGUI_MAINVIEWPORT_H
#define IMLOGDETECTIVE_DEARIMGUI_MAINVIEWPORT_H

struct ImVec2;

namespace ImLogDetective
{
class MainViewPort  
{
public:
    virtual ~MainViewPort() = default;
    virtual ImVec2 getAreaSize() const = 0;
    virtual ImVec2 getWorkAreaSize() const = 0;
    virtual ImVec2 getViewportPosition() const = 0;
    virtual ImVec2 getViewportCenter() const  = 0;
    virtual void setViewportScale(const float scaleFactor) = 0;
};

}

#endif