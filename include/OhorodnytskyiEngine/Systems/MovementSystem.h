#pragma once
#include "OhorodnytskyiEngine/Systems/System.h"
#include "OhorodnytskyiEngine/Entities/Entity.h"

namespace OhorodnytskyiEngine
{
	class MovementSystem : public System
	{
	public:
		void Tick(sf::Time gameTime);
	};
}
