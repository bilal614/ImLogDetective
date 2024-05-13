#pragma once

namespace ImLogDetective
{

class IMainPresenter
{
public:
    virtual ~IMainPresenter() = default;
    virtual void update() = 0;
};

}