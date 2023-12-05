#include "OhorodnytskyiEngine/Managers/ResourcesManager.h"
#include "OhorodnytskyiEngine/Entities/Entity.h"
#include "OhorodnytskyiEngine/Systems/Game.h"

namespace OhorodnytskyiEngine
{
	Entity::Entity(const std::string textureKey)
	{
		_texture = ResourcesManager::GetInstance()->GetTexture(textureKey);

		_sprite.setTexture(*_texture);
		_sprite.setOrigin((sf::Vector2f)_texture->getSize() / 2.f);

		Game::s_transformableEntities.push_back(this);
		Game::s_drawableEntities.push_back(&_sprite);
	}

	sf::Vector2f Entity::GetResultMovementModifier()
	{
		sf::Vector2f result;

		for (auto& movementModifier : _movementModifiers)
		{
			result += movementModifier.second.modifier;
		}

		return result;
	}

	sf::Sprite *Entity::GetSprite()
	{
		return &_sprite;
	}

	void Entity::SetSpeed(float speed)
	{
		_speed = speed;
	}

	float Entity::GetSpeed()
	{
		return _speed;
	}

	void Entity::setPosition(const sf::Vector2f& position)
	{
		_sprite.setPosition(position);
	}

	void Entity::move(float offsetX, float offsetY)
	{
		_sprite.move(offsetX, offsetY);
	}

	void Entity::move(const sf::Vector2f& offset)
	{
		_sprite.move(offset);
	}

	void Entity::rotate(float angle)
	{
		_sprite.rotate(angle);
	}

	float Entity::getRotation()
	{
		return _sprite.getRotation();
	}

	void Entity::RemoveMovementModifier(const std::string movementModifierName)
	{
		_movementModifiers.erase(movementModifierName);
	}

	void Entity::ProcessMove()
	{
		move(GetResultMovementModifier());
	}

	void Entity::AddMovementModifier(MovementModifier movementModifier)
	{
		_movementModifiers.insert({ movementModifier.name, movementModifier });
	}

	void Entity::TrySetMovementModifier(MovementModifier movementModifier)
	{
		if (_movementModifiers.find(movementModifier.name) == _movementModifiers.end())
		{
			_movementModifiers.insert({ movementModifier.name, movementModifier });
		}
		else
		{
			_movementModifiers[movementModifier.name].modifier = movementModifier.modifier;
		}
	}

}