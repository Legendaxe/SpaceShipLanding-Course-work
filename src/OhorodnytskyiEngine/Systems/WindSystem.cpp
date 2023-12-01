#include "OhorodnytskyiEngine/Systems/WindSystem.h"
#include "OhorodnytskyiEngine/Systems/Game.h"

void OhorodnytskyiEngine::WindSystem::SetWind()
{
	MovementModifier windModifier = { "wind", {_windDirection * _windForce, 0} };

	for (auto& entity : Game::s_transformableEntities)
	{
		entity->TrySetMovementModifier(windModifier);
	}
}

OhorodnytskyiEngine::WindSystem::WindSystem()
{
	_windDirection = rand() % 2 == 1 ? LeftToRight : RightToLeft;
	SetWind();
}

void OhorodnytskyiEngine::WindSystem::Tick(sf::Time gameTime)
{
	if ((gameTime - _timeSinceLastWindChange).asSeconds() < 6.0f)
	{
		return;
	}

	_timeSinceLastWindChange = gameTime;

	if (rand() % 2 == 1) // 50% preserve direction of wind
	{
		return;
	}

	_windDirection = _windDirection == LeftToRight ? RightToLeft : LeftToRight;

	SetWind();
}
