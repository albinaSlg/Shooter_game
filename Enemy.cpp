#include "Enemy.h"

const int Enemy::getHealth() const
{
	return _health;
}

void Enemy::updateHealth()
{
	_health = 10;
}

void Enemy::damage(std::vector<std::unique_ptr<Bullet>>& bullets)
{
	for (auto bullet = bullets.begin(); bullet != bullets.end();)
	{
		(*bullet)->update();

		if ((*bullet)->getBounds().intersects(_sprite.getGlobalBounds()))
		{
			_health += -1;
			(*bullet).reset();
			bullet = bullets.erase(bullet);
			std::cout << _health << std::endl;
		}
		else
		{
			bullet++;
		}
	}
}

void Enemy::update(sf::RenderWindow& window, std::vector<std::unique_ptr<Bullet>>& bullets)
{
	_prevPosition = _sprite.getPosition();
	updateActions();
	damage(bullets);
	checkMove(window);
	_text.setPosition(_sprite.getPosition().x, _sprite.getPosition().y - (_sprite.getGlobalBounds().height / 2.f + _fontSize / 2u));
}


