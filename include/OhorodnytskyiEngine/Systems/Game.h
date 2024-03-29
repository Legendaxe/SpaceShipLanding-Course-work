
#pragma once

#include "OhorodnytskyiEngine/Entities/Entity.h"
#include "OhorodnytskyiEngine/Entities/Ship.h"
#include "OhorodnytskyiEngine/Systems/System.h"
#include <vector>


namespace OhorodnytskyiEngine
{

	enum GameState {
		Initializing,
		Running,
		Losed,
		Winned
	};

	class Game : public System
	{
	private:
		sf::RenderWindow* _window;

		Ship* _ship;
		sf::Sprite* _landingPlace;

		void SetupLandingPlace();
		void SetupShip();
	public:
		Game(sf::RenderWindow& window);
		~Game();

		void Tick(sf::Time gameTime);
		void Start();

		void HandleInput(sf::Event& event);

		static void GameEnd(GameState gameState);

		void DeclareCompletion(GameState gameState);

		static std::vector<OhorodnytskyiEngine::System*> s_systems;
		static std::vector<OhorodnytskyiEngine::Entity*> s_transformableEntities;
		static std::vector<sf::Drawable*> s_drawableEntities;
		static std::vector<sf::Sprite*> s_collidableEntities;
		static GameState s_gameState;
	};
}