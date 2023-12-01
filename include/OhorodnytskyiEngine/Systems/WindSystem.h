#pragma once
#include "OhorodnytskyiEngine/Systems/System.h"

namespace OhorodnytskyiEngine
{

	enum WindDirection {
		LeftToRight = 1,
		RightToLeft = -1
	};

	class WindSystem : public System
	{
	private:
		sf::Time _timeSinceLastWindChange;

		WindDirection _windDirection;

		float _windForce = .5f;

		void SetWind();

	public:
		WindSystem();

		void Tick(sf::Time gameTime);
	};

}