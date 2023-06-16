#pragma once

#include "event_handling/IEventLoop.h"
#include <functional>
#include <memory>

namespace LogAnalyzerTool
{

class EventLoop : public IEventLoop<EventLoop>
{
public:
    EventLoop();
    ~EventLoop();
    EventLoop(EventLoop&&);
    EventLoop& operator=(EventLoop&&);

    EventLoop(const EventLoop&) = delete;
    EventLoop& operator=(const EventLoop&) = delete;

    void post(const std::function<void()>&) final;

    void post(void (*)()) final;

    void start() final;

    void stop() final;

    template<typename T, typename ...A>
    void post(const std::function<T(A...)>& f, A&&... args) {
        post([&]() -> void {f(std::forward<A>(args)...);});
    }

private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}