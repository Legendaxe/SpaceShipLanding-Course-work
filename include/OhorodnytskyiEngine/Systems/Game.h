
#pragma once

#include "OhorodnytskyiEngine/Entities/Entity.h"
#include "OhorodnytskyiEngine/Systems/System.h"
#include <vector>


namespace OhorodnytskyiEngine
{

	enum GameState {
		Running,
		Losed,
		Winned
	};

	class Game : public System
	{
	private:
		sf::RenderWindow* _window;

		void Win();
		void Lost();
	public:
		Game(sf::RenderWindow& window);

		void Tick(sf::Time gameTime);

		static void GameEnd(GameState gameState);

		static std::vector<OhorodnytskyiEngine::System*> s_systems;
		static std::vector<OhorodnytskyiEngine::Entity*> s_transformableEntities;
		static std::vector<sf::Drawable*> s_drawableEntities;
		static std::vector<sf::Sprite*> s_collidableEntities;
		static GameState s_gameState;
	};
}