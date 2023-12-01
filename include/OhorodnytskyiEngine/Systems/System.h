#pragma once
#include <SFML/Graphics.hpp>

namespace OhorodnytskyiEngine
{
	class System
	{
	private:
		bool _running = false;
	public:
		virtual void Start();
		virtual void Stop();
		virtual void Tick(sf::Time gameTime) = 0;
	};

}