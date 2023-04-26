#include "Player.h"

void Player::setupBullet(const TexturePtr& bulletTexture)
{
	_bulletTexture.reset();
	_bulletTexture = bulletTexture;
}

void Player::updateActions(sf::RenderWindow& window)
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
	if (sf::Mouse::isButtonPressed(_controls.attack) && canAttack())
	{
		sf::Vector2i coords = sf::Mouse::getPosition(window);

		sf::Vector2f playerPos = _sprite.getPosition();

		sf::Vector2f direction = { coords.x - playerPos.x, coords.y - playerPos.y };
		float lenght = sqrt(direction.x * direction.x + direction.y * direction.y);
		direction.x /= lenght;
		direction.y /= lenght;

		_bullets.push_back(std::make_unique<Bullet>(_bulletTexture, _sprite.getPosition(), direction));
	}
}

void Player::updateAttack()
{
	_attackCooldownCur = _clock.getElapsedTime();
}

void Player::update(sf::RenderWindow& window)
{
	_prevPosition = _sprite.getPosition();
	updateAttack();
	updateBullets(window);
	updateActions(window);
	checkMove(window);
	_text.setPosition(_sprite.getPosition().x, _sprite.getPosition().y - (_sprite.getGlobalBounds().height / 2.f + _fontSize / 2u));
}

std::vector<std::unique_ptr<Bullet>>& Player::getBullets()
{
	return _bullets;
}

const bool Player::canAttack()
{
	if (_attackCooldownCur >= _attackCooldownMax)
	{
		_clock.restart();
		return true;
	}
	return false;
}

void Player::updateBullets(sf::RenderWindow& window)
{
	for (auto bullet = _bullets.begin(); bullet != _bullets.end();)
	{
		(*bullet)->update();

		if ((*bullet)->isOutOfWindow(window))
		{
			(*bullet).reset();
			bullet = _bullets.erase(bullet);
		}
		else
		{
			bullet++;
		}
	}
}

void Player::drawBullets(sf::RenderTarget& target) const
{
	for (auto& bullet : _bullets)
	{
		bullet->draw(target);
	}
}