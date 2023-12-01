#include "OhorodnytskyiEngine/Entities/Bird.h"
#include "OhorodnytskyiEngine/Systems/Game.h"


namespace OhorodnytskyiEngine
{
	Bird::Bird(const std::string fileName) : Entity(fileName)
	{
		Game::s_collidableEntities.push_back(GetSprite());
	}
}