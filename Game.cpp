#include "Game.h"
#include <boost/algorithm/string.hpp>

using boost::algorithm::to_upper_copy;

namespace 
{
	template<typename T>
	void LoadResource(std::map<std::string, std::shared_ptr<T>>& resources, std::filesystem::path path, std::string key) noexcept(false)
	{
		resources[key] = std::make_shared<T>();

		if (!resources[key]->loadFromFile(path.string()))
			throw std::runtime_error("Can't load " + key + " texture");
	}
}

void Game::initWindow()
{
	_window.get()->create(sf::VideoMode(_width, _height), "Game");

	_window->setFramerateLimit(144);
	_window->setVerticalSyncEnabled(false);
}

void Game::loadTextures() noexcept(false)
{
	LoadResource<sf::Texture>(_textures, _paths.textures.player, "Player");
	LoadResource<sf::Texture>(_textures, _paths.textures.enemy, "Enemy");
	LoadResource<sf::Texture>(_textures, _paths.textures.bullet, "Bullet");
}

void Game::loadFonts() noexcept(false)
{
	LoadResource<sf::Font>(_fonts, _paths.fonts.player, "Player");
	LoadResource<sf::Font>(_fonts, _paths.fonts.stats, "Stats");
}

void Game::initPlayers()
{
	sf::Vector2f position = { static_cast<float>(_window.get()->getSize().x - _window.get()->getSize().x / 5), static_cast<float>(_window.get()->getSize().y / 2) };
	_player->setup(_fonts["Player"], _textures["Player"], position, 0.5f, to_upper_copy(std::string("cat")));
	_player->setupBullet(_textures["Bullet"]);
	_player.get()->setControls({ sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D, sf::Mouse::Left });

	position = { static_cast<float>(_window.get()->getSize().x / 5.f), static_cast<float>(_window.get()->getSize().y / 2.f) };
	_enemy->setup(_fonts["Player"], _textures["Enemy"], position, 0.1f, to_upper_copy(std::string("enemy")));
}

void Game::initText()
{
	//Game over text
	_gameOver.setFont(*_fonts["Player"]);
	_gameOver.setCharacterSize(24u);
	_gameOver.setString(to_upper_copy(std::string ("game over")));
	auto textSizeGameOver = _gameOver.getGlobalBounds();
	_gameOver.setOrigin(static_cast<float>(textSizeGameOver.width / 2u), static_cast<float>(textSizeGameOver.height / 2u));
	_gameOver.setPosition(static_cast<float>(_window->getSize().x / 2), static_cast<float>(_window->getSize().y / 2));

	//Restart text
	_restart.setFont(*_fonts["Player"]);
	_restart.setCharacterSize(20u);
	_restart.setString(to_upper_copy(std::string("TRY AGAIN?")));
	textSizeGameOver = _restart.getGlobalBounds();
	_restart.setOrigin(static_cast<float>(textSizeGameOver.width / 2u), static_cast<float>(textSizeGameOver.height / 2u));
	_restart.setPosition(_gameOver.getPosition().x, _gameOver.getPosition().y + _gameOver.getGlobalBounds().height + _restart.getGlobalBounds().height / 2);

	//Stats setString(to_upper_copy(std::string ("game over")));text
	_stats.setFont(*_fonts["Stats"]);
	_stats.setCharacterSize(36u);
	_stats.setFillColor(sf::Color::Red);
	_stats.setString(std::to_string(_enemy->getHealth()));
	auto textSizeStats = _stats.getGlobalBounds();
	_stats.setOrigin(static_cast<float>(textSizeStats.width / 2u), static_cast<float>(textSizeStats.height / 2u));
	_stats.setPosition(_stats.getGlobalBounds().width / 2, _stats.getGlobalBounds().height / 2);
}

bool Game::gameContinuation()
{
	if (_enemy->getHealth() <= 0)
		_isGame = false;
	else 
		_isGame = true;
	return _isGame;
}

bool Game::restart()
{
	if (_restart.getGlobalBounds().contains(sf::Mouse::getPosition(*_window.get()).x, sf::Mouse::getPosition(*_window.get()).y) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		return true;
	}
	return false;
}

void Game::create() noexcept(false)
{
	initWindow();
	loadTextures();
	loadFonts();
	initPlayers();
	initText();
}

void Game::checkEvent()
{
	sf::Event event;

	while (_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			_window->close();
		}
		if (event.type == sf::Event::Resized)
		{
			std::string windowName = std::to_string(_window->getSize().x) + " " + std::to_string(_window->getSize().y);
			_window->setTitle(windowName);
		}
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				_window->close();
			}
		}
	}
}

void Game::updateStats()
{
	_stats.setString(std::to_string(_enemy->getHealth()) + " HP");
}

void Game::update()
{
	_player->update(*_window);
	_enemy->update(*_window, _player->getBullets());
	updateStats();
}

void Game::drawStats() const
{
	_window->draw(_stats);
}

void Game::draw() const
{
	_window->clear(sf::Color::Black);

	_player->draw(*_window);
	_enemy->draw(*_window);
	_player->drawBullets(*_window);
	drawStats();

	_window->display();
}

void Game::drawGameOver() const
{
	_window->clear(sf::Color::Black);
	_window->draw(_gameOver);
	_window->draw(_restart);
	_window->display();
}

void Game::run()
{
	while (_window->isOpen())
	{
		if (gameContinuation())
		{
			checkEvent();
			update();
			_time->restart();
			draw();
		}
		else
		{
			checkEvent();
			drawGameOver();
			if (restart())
			{
				using namespace std::chrono_literals;
				_enemy->updateHealth();
				std::this_thread::sleep_for(1000ms);
			}
		}
	}
}
