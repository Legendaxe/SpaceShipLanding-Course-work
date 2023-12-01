#include "OhorodnytskyiEngine/Systems/Game.h"
#include "OhorodnytskyiEngine/Systems/MovementSystem.h"
#include "OhorodnytskyiEngine/Systems/WindSystem.h"

namespace OhorodnytskyiEngine
{
	Game::Game(sf::RenderWindow& window)
	{
		_window = &window;

		s_systems.push_back(new MovementSystem());
		s_systems.push_back(new WindSystem());

		Start();
	}

	void Game::Tick(sf::Time gameTime)
	{
		for (auto& system : Game::s_systems)
		{
			system->Tick(gameTime);
		}

		switch (s_gameState)
		{
		case Losed:
			Lost();
			break;
		case Winned:
			Win();
			break;
		}
	}

	void Game::Win()
	{
		_window->clear(sf::Color::Red);
		sf::sleep(sf::Time(sf::seconds(5000)));
	}

	void Game::Lost()
	{
		_window->clear(sf::Color::Yellow);
		sf::sleep(sf::Time(sf::seconds(5000)));
	}

	void Game::GameEnd(GameState gameState)
	{
		s_drawableEntities.clear();
		s_drawableEntities.shrink_to_fit();
		
		s_gameState = gameState;
	}

	std::vector<Entity*> Game::s_transformableEntities;
	std::vector<System*> Game::s_systems;
	std::vector<sf::Drawable*> Game::s_drawableEntities;
	std::vector<sf::Sprite*> Game::s_collidableEntities;
	GameState Game::s_gameState = Running;
}
