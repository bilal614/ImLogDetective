#pragma once

#include <functional>

namespace LogAnalyzerTool
{

template <typename D>
class IEventLoop
{
public:
    virtual ~IEventLoop() = default;

    virtual void post(const std::function<void()>&) = 0;

    virtual void post(void (*)()) = 0;

    virtual void start() = 0;

    virtual void stop() = 0;

    template<typename T, typename ...A>
    void post(const std::function<T(A...)>& f, A&&... args) {
        static_cast<D*>(this)->post([&]() -> void {
            f(std::forward<A>(args)...);
        });
    }
};

}