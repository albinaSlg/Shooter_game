#pragma once
#include"Entity.h"

class Enemy final : public Entity
{
public:
	const int getHealth() const;

	void updateHealth();

	void damage(std::vector<std::unique_ptr<Bullet>>& bullets);
	void update(sf::RenderWindow& window, std::vector<std::unique_ptr<Bullet>>& bullets);

private:
	int _health = 10;
};

