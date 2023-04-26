#pragma once
#include <SFML/Graphics.hpp>

class Time
{
public:
	Time(const Time& time) = delete;
	void operator= (const Time& time) = delete;

	static Time* getInstance();
	const sf::Time getTime() const;
	void restart();

private:
	Time() = default;

private:
	static std::unique_ptr<Time> _instance;
	sf::Clock _clock;
};

