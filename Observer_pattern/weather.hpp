#pragma once

#include "observ.hpp"
#include <iostream>

/*
 * Weather data
 * Using observable object interface.
 * Collects Data from site and notify displays.
*/

class WeatherData : public IObservable
{
private:
    std::list<IObserver *> observers_list_;

    void attach(IObserver* obs)
    {
        observers_list_.push_back(obs);
    }

    void detach(IObserver* obs)
    {
        std::list<IObserver *>::iterator it;
        std::find(observers_list_.begin(),
                    observers_list_.end(), obs);
        if (it != observer_list_.end())
            observer_list_.erase(it);
    }

    void notify()
    {
        for (auto it = observers_list_.begin();
                it != observers_list_.end(); it++)
            it->update();
    }

public:
    WeatherData() {};
    
    double get_temperature() const;
    double get_humidity() const;
    double get_pressuer() const;
};


/* 
 * Weaher Displays
 * Updating and print information to console
 * when observable WeatherData notify (update) them.
 */

class IWeatherDisplay : public IObserver
{
protected::
    int ID = -1;

public:
    ~IWeatherDisplay () {}
    void display() const = 0;
}

class TempertureDisplay : public IWeatherDisplay
{
private:
    double temp_ = 0. / 0.;

public:
    TemperatureDisplay()
        : temp_(0. / 0.)
    {}

    void display() const 
    {
        std::cout << "=====================================" << std::endl;
        std::cout << "Temperature Display with ID : " << ID << std::endl;
        std::cout << std:: endl << "Cureent temperature is : ";
        std::cout << "[ " << temp_ <, " ]" << std::endl << std::cout << temp_;
        std::cout << "=====================================" << std::endl;
    }
}
