#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <OhorodnytskyiEngine/MovementModifier.h>

namespace OhorodnytskyiEngine
{
	class Entity : public sf::Transformable
	{
	protected:

		sf::Texture* _texture;
		sf::Sprite _sprite;

		float _speed = 1;
		
		std::unordered_map<std::string, MovementModifier> _movementModifiers;

	public:
		Entity(std::string filePath = "Resources/Honk.png");

		sf::Sprite *GetSprite();

		void move(float offsetX, float offsetY);
		void move(const sf::Vector2f &offset);

		sf::Vector2f GetResultMovementModifier();

		void rotate(float angle);
		float getRotation();


		void SetSpeed(float speed);
		float GetSpeed();

		void setPosition(const sf::Vector2f& position);

		

		void AddMovementModifier(MovementModifier movementModifier);

		void TrySetMovementModifier(MovementModifier movementModifier);

		void RemoveMovementModifier(const std::string movementModifierName);

		virtual void ProcessMove();
	};
}
