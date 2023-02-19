#pragma once
#include <algorithm>
#include <list>

class ISubscriber {
public:
    virtual void update() = 0;
    virtual ~ISubscriber() = default;
};

class IObserver {
public:
    virtual void notify() = 0;
    virtual void subscribe(ISubscriber *) = 0;
    virtual void unsubscribe(ISubscriber *) = 0;
    virtual ~IObserver() = default;

protected:
    std::list<ISubscriber *> _subscribers;

    bool _is_subscribed(ISubscriber *subscriber)
    {
        return (std::find(_subscribers.begin(), _subscribers.end(), subscriber) != _subscribers.end());
    }
};
