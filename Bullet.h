#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include <numbers>
#include <iostream>
#include "Time.h"

using TexturePtr = std::shared_ptr<sf::Texture>;

class Bullet
{
private:

public:
	Bullet(const TexturePtr& texture, const sf::Vector2f& position, const sf::Vector2f& direction);
	Bullet(const Bullet& bullet) = delete;
	Bullet& operator=(const Bullet& bullet) = delete;
	~Bullet() = default;

	void scale(float scale);

	const sf::FloatRect getBounds() const;
	const bool isOutOfWindow(sf::RenderWindow& window) const;

	void move();
	void update();
	void draw(sf::RenderTarget& target) const;

private:
	sf::Sprite _sprite;
	sf::Vector2f _direction;
	float _movementSpeed = 0.3f;
	Time* _time = Time::getInstance();
};

