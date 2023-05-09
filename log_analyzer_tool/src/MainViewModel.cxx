#include "MainViewModel.h"

#include <iostream>


namespace LogAnalyzerTool
{

struct MainViewModel::Impl
{
    Impl();
    ~Impl() = default;

    Event<> validationEvent;
};

MainViewModel::Impl::Impl() :
    validationEvent{}
{
}


MainViewModel::MainViewModel() :
    p{std::make_unique<Impl>()}
{
    addValidationHandler([this](){
        std::cout <<"Hello" << std::endl;
    });
}

MainViewModel::~MainViewModel() = default;

void MainViewModel::addValidationHandler(const EventHandlerFuntion<>& func)
{
    p->validationEvent.add(func);
}

}