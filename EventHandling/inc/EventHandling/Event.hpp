#pragma once

#include "IEvent.h"
#include <vector>

namespace LogEventHandling
{

template<typename ...A>
class Event : public IEvent<A...>
{
public:
    Event() :
        m_delegates{},
        m_eventCompletionHandler{}
    {
    }

    Event(const std::function<void()>& completionHandler) :
        m_delegates{},
        m_eventCompletionHandler{completionHandler}
    {
    }

    ~Event() = default;

    void registerDelegate(const std::function<void(A...)>& delegate) override
    {
        m_delegates.push_back(delegate);
    }

    void clearDelegates() override
    {
        m_delegates.clear();
    }

    void operator()(A&&... args) override
    {
        for(auto& delegate : m_delegates)
        {
            delegate(args...);
        }
        if(m_eventCompletionHandler)
        {
            m_eventCompletionHandler();
        }
    }

private:
    std::vector<std::function<void(A...)>> m_delegates;
    std::function<void()> m_eventCompletionHandler;
};

}