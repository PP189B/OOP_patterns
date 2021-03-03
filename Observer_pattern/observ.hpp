#pragma once

#include <list>

/* Interfces */

class IObserver
{
public:
    ~IObserver() {}
    void update() = 0;
};

class IObservable
{
public:
    ~IObservable() {};

    void attach(IObserver *obs) = 0;
    void detach(IObserver *obs) = 0;
    void notify() = 0;
};
