#include "OhorodnytskyiEngine/Systems/MovementSystem.h"
#include "OhorodnytskyiEngine/Systems/Game.h"

namespace OhorodnytskyiEngine
{
	void MovementSystem::Tick(sf::Time gameTime)
	{
		if (!_running)
		{
			return;
		}

		for (auto& entity : Game::s_transformableEntities)
		{
			entity->ProcessMove();
		}
	}
}