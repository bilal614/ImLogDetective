#pragma once

#include "event_handling/IEvent.h"
#include <vector>

namespace LogAnalyzerTool
{

class Event : public IEvent
{
public:
    Event(const std::function<void()>& completionHandler) :
        m_delegates{},
        m_eventCompletionHandler{completionHandler}
    {
    }

    ~Event() = default;

    void registerDelegate(const std::function<void()>& delegate) override
    {
        m_delegates.push_back(delegate);
    }

    void clearDelegates() override
    {
        m_delegates.clear();
    }

    void operator()() override
    {
        for(auto& delegate : m_delegates)
        {
            delegate();
        }
        m_eventCompletionHandler();
    }

private:
    std::vector<std::function<void()>> m_delegates;
    std::function<void()> m_eventCompletionHandler;
};

}