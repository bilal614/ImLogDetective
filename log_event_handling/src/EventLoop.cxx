
#include "event_handling/EventLoop.h"
#include <condition_variable>
#include <forward_list>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <deque>
#include <thread>
#include <utility>

#include <iostream>

namespace LogEventHandling
{

struct EventLoop::Impl
{
    using CallbackType = std::function<void()>;

    Impl();
    ~Impl();
    void process();

    std::unique_ptr<std::mutex> mut;
    std::unique_ptr<std::thread> thread;
    std::condition_variable nonEmptyQueuCond;
    std::deque<CallbackType> callbacks;
    bool running;

    std::promise<bool> startedProcessing;
    std::future<bool> startedProcessingFuture;
};

EventLoop::Impl::Impl() :
    running{false},
    startedProcessingFuture{startedProcessing.get_future()}
{
}

EventLoop::Impl::~Impl()
{
    if(thread && thread->joinable())
    {
        thread->join();
    }
}

void EventLoop::Impl::process()
{
    mut = std::make_unique<std::mutex>();
    startedProcessing.set_value(true);
    while(running)
    {
        std::unique_ptr<CallbackType> f;
        {
            std::unique_lock<std::mutex> lk(*mut);
            nonEmptyQueuCond.wait(lk, [&](){ return !callbacks.empty();});
            f = std::make_unique<CallbackType>(std::move(callbacks.front()));
            callbacks.pop_front();
        }
        if(f)
        {
            (*f)();
        }
    }
}

EventLoop::EventLoop() :
    p{std::make_unique<Impl>()}
{
}

EventLoop::~EventLoop()
{
    stop();
}

size_t EventLoop::size()
{
    std::lock_guard<std::mutex> lk(*p->mut);
    return p->callbacks.size();
}

void EventLoop::post(const std::function<void()>& f)
{
    std::lock_guard<std::mutex> lk(*p->mut);
    p->callbacks.emplace_back(f);
    p->nonEmptyQueuCond.notify_one();
}

void EventLoop::post(void (*f)())
{
    post(f);
}

void EventLoop::start()
{
    if(!p->running)
    {
        p->running = true;
        p->thread = std::make_unique<std::thread>(&EventLoop::Impl::process, p.get());
        auto processing = p->startedProcessingFuture.get();
    }
}

void EventLoop::stop()
{
    if(p->running)
    {
        post([&](){
            p->running = false;
        });
    }
}

}