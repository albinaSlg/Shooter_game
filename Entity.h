#pragma once
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include "Bullet.h"
#include "Time.h"

using TexturePtr = std::shared_ptr<sf::Texture>;
using FontPtr = std::shared_ptr<sf::Font>;

struct ControlConfig
{
	sf::Keyboard::Key up;
	sf::Keyboard::Key down;
	sf::Keyboard::Key left;
	sf::Keyboard::Key right;
	sf::Mouse::Button attack;
};

class Entity
{
public:
	Entity() = default;
	Entity(std::string name);
	Entity(const Entity& entity) = default;
	Entity& operator= (const Entity& entity) = delete;
	~Entity() = default;

	void setup(const FontPtr& font, const TexturePtr& texture, const sf::Vector2f& position, float scaleValue, const std::string& name = "ENTITY");
	void scale(float scale);
	void setControls(const ControlConfig& controls);
	void setName(const std::string& name);

	void move(float directionX, float directionY);
	void checkMove(sf::RenderWindow& window);
	void update(sf::RenderWindow& window);
	void draw(sf::RenderTarget& target) const;
	virtual void updateActions();

protected:
	void initSprite(const TexturePtr& texture, const sf::Vector2f& position, float scale);
	void initText(const FontPtr& font);

protected:
	sf::Sprite _sprite;
	sf::Text _text;
	std::string _name;
	unsigned int _fontSize = 16u;
	float _movementSpeed = 0.5f;
	ControlConfig _controls = { sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right, sf::Mouse::Right };
	sf::Vector2f _prevPosition = { 0.f, 0.f };
	Time* _time = Time::getInstance();
};

