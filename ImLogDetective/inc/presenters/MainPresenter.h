
#ifndef IMLOGDETECTIVE_PRESENTERS_MAINPRESENTER_H
#define IMLOGDETECTIVE_PRESENTERS_MAINPRESENTER_H

namespace ImLogDetective
{

class MainPresenter
{
public:
    virtual ~MainPresenter() = default;
    virtual void update() = 0;
};

}

#endif