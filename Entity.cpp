#include "Entity.h"

Entity::Entity(std::string name) :
	_name(name)
{
}

void Entity::initSprite(const TexturePtr& texture, const sf::Vector2f& position, float scaleValue)
{
	_sprite.setTexture(*texture.get());
	scale(scaleValue);
	_sprite.setPosition(position);

	auto textureSize = (*texture.get()).getSize();
	_sprite.setOrigin(static_cast<float>(textureSize.x / 2u), static_cast<float>(textureSize.y / 2u));
}

void Entity::initText(const FontPtr& font)
{
	_text.setFont(*font);
	_text.setString(_name);
	_text.setCharacterSize(_fontSize);

	auto textSize = _text.getGlobalBounds();
	_text.setOrigin(static_cast<float>(textSize.width / 2u), static_cast<float>(textSize.height / 2u));
}

void Entity::setup(const FontPtr& font, const TexturePtr& texture, const sf::Vector2f& position, float scaleValue, const std::string& name)
{
	setName(name);
	initSprite(texture, position, scaleValue);
	initText(font);
}

void Entity::scale(float scale)
{
	_sprite.scale(scale, scale);
}

void Entity::setControls(const ControlConfig& controls)
{
	_controls = controls;
}

void Entity::setName(const std::string& name)
{
	_name = name;
}

void Entity::move(float directionX, float directionY)
{
	_sprite.move(_movementSpeed * directionX * _time->getTime().asMilliseconds(), _movementSpeed * directionY * _time->getTime().asMilliseconds());
}

void Entity::checkMove(sf::RenderWindow& window)
{
	if (_sprite.getGlobalBounds().left < 0.f)
		_sprite.setPosition(_prevPosition);
	if (_sprite.getGlobalBounds().left + _sprite.getGlobalBounds().width > window.getSize().x)
		_sprite.setPosition(_prevPosition);
	if (_sprite.getGlobalBounds().top < 0.f)
		_sprite.setPosition(_prevPosition);
	if (_sprite.getGlobalBounds().top + _sprite.getGlobalBounds().height > window.getSize().y)
		_sprite.setPosition(_prevPosition);
}

void Entity::update(sf::RenderWindow& window)
{
	_prevPosition = _sprite.getPosition();
	updateActions();
	checkMove(window);
	_text.setPosition(_sprite.getPosition().x, _sprite.getPosition().y - (_sprite.getGlobalBounds().height / 2.f + _fontSize / 2u));
}

void Entity::updateActions()
{
	if (sf::Keyboard::isKeyPressed(_controls.right))
	{
		move(1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(_controls.left))
	{
		move(-1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(_controls.up))
	{
		move(0.f, -1.f);
	}
	if (sf::Keyboard::isKeyPressed(_controls.down))
	{
		move(0.f, 1.f);
	}
}

void Entity::draw(sf::RenderTarget& target) const
{
	target.draw(_sprite);
	target.draw(_text);
}
