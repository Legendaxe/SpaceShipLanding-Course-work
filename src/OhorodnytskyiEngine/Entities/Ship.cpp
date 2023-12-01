#define _USE_MATH_DEFINES

#include "OhorodnytskyiEngine/Entities/Ship.h"
#include "OhorodnytskyiEngine/Systems/Game.h"
#include <math.h>

namespace OhorodnytskyiEngine
{
	Ship::Ship(const std::string filePath) : Entity(filePath)
	{
		SetSpeed(2.5f);
		_engineStarted = false;
		Game::s_collidableEntities.push_back(GetSprite());
	}

	void Ship::StartEngine()
	{
		_engineStarted = true;
	}

	void Ship::StopEngine()
	{
		_engineStarted = false;
	}
	void Ship::ProcessMove()
	{
		if (_engineStarted)
		{
			float angle = getRotation() * M_PI / 180;
			float sinOfRotation = sinf(angle);
			float cosOfRotation = cosf(angle);

			sf::Vector2f engineVector = { sinOfRotation, -cosOfRotation };
			TrySetMovementModifier({ "engine-on", engineVector * GetSpeed()});
		}
		else
		{
			RemoveMovementModifier("engine-on");
		}
		
		sf::Vector2f resultMovementModifier = GetResultMovementModifier();

		if (resultMovementModifier == sf::Vector2f(0, 0))
		{
			return;
		}

		move(resultMovementModifier);

		sf::IntRect thisIntRect = _sprite.getTextureRect();

		for (auto collidableSprite : Game::s_collidableEntities)
		{
			if (collidableSprite->getGlobalBounds().intersects(_sprite.getGlobalBounds()) && &_sprite != collidableSprite)
			{
				move(-resultMovementModifier);
				Game::GameEnd(Losed);
				break;
			}
		}
	}

	void Ship::rotate(float angle)
	{
		_sprite.rotate(angle);

		for (auto collidableSprite : Game::s_collidableEntities)
		{
			if (collidableSprite->getGlobalBounds().intersects(_sprite.getGlobalBounds()) && &_sprite != collidableSprite)
			{
				_sprite.rotate(-angle);
				break;
			}
		}
	}
}