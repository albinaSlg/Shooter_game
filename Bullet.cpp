#include "Bullet.h"

Bullet::Bullet(const TexturePtr& texture, const sf::Vector2f& position, const sf::Vector2f& direction) :
	_direction(direction)
{
	_sprite.setTexture(*texture);
	scale(0.05f);
	_sprite.setPosition(position);
	_sprite.setRotation(acosf(direction.x) * 180.f / static_cast<float>(std::numbers::pi) * (direction.y / abs(direction.y)));
}

void Bullet::scale(float scale)
{
	_sprite.scale(scale, scale);
}

const sf::FloatRect Bullet::getBounds() const
{
	return _sprite.getGlobalBounds();
}

const bool Bullet::isOutOfWindow(sf::RenderWindow& window) const
{
	if (_sprite.getGlobalBounds().top + _sprite.getGlobalBounds().height < 0.f ||
		_sprite.getGlobalBounds().left + _sprite.getGlobalBounds().width < 0.f ||
		_sprite.getGlobalBounds().top > window.getSize().y ||
		_sprite.getGlobalBounds().left > window.getSize().x)
		return true;
	else
		return false;
}

void Bullet::move()
{
	_sprite.move(_movementSpeed * _direction.x * _time->getTime().asMilliseconds(), _movementSpeed * _direction.y * _time->getTime().asMilliseconds());
}

void Bullet::update()
{
	move();
}

void Bullet::draw(sf::RenderTarget& target) const
{
	target.draw(_sprite);
}
