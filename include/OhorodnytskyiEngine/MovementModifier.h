#pragma once
#include <string>
#include <SFML/System/Vector2.hpp>

struct MovementModifier
{
	const std::string name;
	sf::Vector2f modifier;
};

