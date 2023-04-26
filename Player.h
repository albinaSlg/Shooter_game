#pragma once
#include "Entity.h"

class Player final : public Entity
{
public:	
	void setupBullet(const TexturePtr& bulletTexture);
	void update(sf::RenderWindow& window);
	std::vector<std::unique_ptr<Bullet>>& getBullets();
	void drawBullets(sf::RenderTarget& target) const;

private:
	void updateActions(sf::RenderWindow& window);
	void updateAttack();
	void updateBullets(sf::RenderWindow& window);
	const bool canAttack();

private:
	sf::Clock _clock;
	TexturePtr _bulletTexture;
	std::vector<std::unique_ptr<Bullet>> _bullets;
	bool _isAllowedToAttack = false;
	sf::Time _attackCooldownCur = sf::seconds(0.25);
	sf::Time _attackCooldownMax = sf::seconds(0.25);
};

