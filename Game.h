#pragma once
#include <map>
#include <thread>
#include "Enemy.h"
#include "Player.h"
#include "Time.h"

using mapTextures = std::map<std::string, std::shared_ptr<sf::Texture>>;
using mapFonts = std::map<std::string, std::shared_ptr<sf::Font>>;

struct Paths
{
	struct Textures
	{
		std::filesystem::path bullet;
		std::filesystem::path player;
		std::filesystem::path enemy;
	}textures;

	struct Fonts
	{
		std::filesystem::path player;
		std::filesystem::path stats;
	}fonts;
};

class Game
{
public:
	Game() = default;
	~Game() = default;
	void create() noexcept(false);
	void checkEvent();
	void updateStats();
	void update();
	void drawStats() const;
	void draw() const;
	void drawGameOver() const;
	void run();

private:
	void initWindow();
	void loadTextures() noexcept(false);
	void loadFonts() noexcept(false);
	void initPlayers();
	void initText();

	bool gameContinuation();
	bool restart();

private:
	std::unique_ptr<sf::RenderWindow> _window = std::make_unique<sf::RenderWindow>();
	std::unique_ptr<Player> _player = std::make_unique<Player>();
	std::unique_ptr<Enemy> _enemy = std::make_unique<Enemy>();
	sf::Text _stats;
	sf::Text _gameOver;
	sf::Text _restart;
	Paths _paths = { {"Texture/bullet.png", "Texture/player.png", "Texture/enemy.png"}, {"Font/player.ttf", {"Font/stats.otf"} } };
	mapTextures _textures;
	mapFonts _fonts;
	unsigned int _width = 800u;
	unsigned int _height = 600u;
	bool _isGame = true;
	Time* _time = Time::getInstance();
};

