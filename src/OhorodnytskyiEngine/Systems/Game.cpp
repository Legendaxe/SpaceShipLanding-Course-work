#include "DEFINES/defines.h"
#include "OhorodnytskyiEngine/Systems/Game.h"
#include "OhorodnytskyiEngine/Systems/MovementSystem.h"
#include "OhorodnytskyiEngine/Systems/WindSystem.h"
#include "OhorodnytskyiEngine/Managers/ResourcesManager.h"


namespace OhorodnytskyiEngine
{
	Game::Game(sf::RenderWindow& window)
	{
		_window = &window;

		SetupShip();

		SetupLandingPlace();

		s_systems.push_back(new MovementSystem());
		s_systems.push_back(new WindSystem());

		Start();
	}

	Game::~Game()
	{
		delete _ship;
		delete _landingPlace;
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

		sf::Text completionText;
		completionText.setPosition(WINDOW_WIDTH / 2 - 80, WINDOW_HEIGHT / 2 - 20);
		completionText.setFont(*ResourcesManager::GetInstance()->GetFont("arial"));
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

	void Game::HandleInput(sf::Event& event)
	{
		while (_window->pollEvent(event))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				_ship->StartEngine();
			}
			else
			{
				_ship->StopEngine();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				_ship->rotate(-ROTATE_ANGLE);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				_ship->rotate(ROTATE_ANGLE);
			}

			if (event.type == sf::Event::Closed)
				_window->close();
		}
	}

	void Game::SetupLandingPlace()
	{
		_landingPlace = new sf::Sprite();

		sf::Texture* texture = ResourcesManager::GetInstance()->GetTexture("landing_place");

		_landingPlace->setTexture(*texture);
		_landingPlace->setPosition(WINDOW_WIDTH - 450, WINDOW_HEIGHT - 20);

		s_drawableEntities.push_back(_landingPlace);
		s_collidableEntities.push_back(_landingPlace);
	}

	void Game::SetupShip()
	{
		_ship = new Ship();

		_ship->AddMovementModifier({ "gravity", {0, 1} });
		_ship->setPosition({ WINDOW_WIDTH - 400, WINDOW_HEIGHT - 600 });
	}

	std::vector<Entity*> Game::s_transformableEntities;
	std::vector<System*> Game::s_systems;
	std::vector<sf::Drawable*> Game::s_drawableEntities;
	std::vector<sf::Sprite*> Game::s_collidableEntities;
	GameState Game::s_gameState = Initializing;
}
