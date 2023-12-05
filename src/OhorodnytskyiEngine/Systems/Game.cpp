#include "DEFINES/defines.h"
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
		if (!_running)
		{
			return;
		}

		switch (s_gameState)
		{
		case Losed:
			DeclareCompletion(Losed);
			return;
		case Winned:
			DeclareCompletion(Winned);
			return;
		}

		for (auto& system : Game::s_systems)
		{
			system->Tick(gameTime);
		}
	}

	void Game::Start()
	{
		_running = true;

		for (auto& system : Game::s_systems)
		{
			system->Start();
		}
	}

	void Game::DeclareCompletion(GameState gameState)
	{
		_running = false;

		_window->clear(gameState == Winned ? sf::Color::Green : sf::Color::Red);

		sf::Font arialFont;
		arialFont.loadFromFile("Resources/arial.ttf");

		sf::Text completionText;
		completionText.setPosition(WINDOW_WIDTH / 2 - 80, WINDOW_HEIGHT / 2 - 20);
		completionText.setFont(arialFont);
		completionText.setString(gameState == Winned ? "You Win!" : "You Lose...");

		_window->draw(completionText);
		_window->display();

		sf::sleep(sf::Time(sf::seconds(10)));
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
	GameState Game::s_gameState = Initializing;
}
