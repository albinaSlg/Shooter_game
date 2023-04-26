#include "Time.h"

Time* Time::getInstance()
{
    if (_instance == nullptr)
        _instance = std::unique_ptr<Time>(new Time);
    return _instance.get();
}

void Time::restart()
{
    _clock.restart();
}

const sf::Time Time::getTime() const
{
    return _clock.getElapsedTime();
}

std::unique_ptr<Time> Time::_instance;
