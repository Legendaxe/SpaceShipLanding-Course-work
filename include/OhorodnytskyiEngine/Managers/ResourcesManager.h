#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

namespace OhorodnytskyiEngine
{
	class ResourcesManager
	{
	private:
		ResourcesManager() {};

		static ResourcesManager* resourcesManager_;

		std::unordered_map<std::string, sf::Texture> _textures;
		std::unordered_map<std::string, sf::Font> _fonts;
	public:
		ResourcesManager(ResourcesManager&) = delete;
		void operator=(const ResourcesManager&) = delete;

		bool AddTextureFromFile(std::string filePath, std::string textureKey);
		bool AddFontFromFile(std::string filePath, std::string fontKey);

		sf::Texture* GetTexture(std::string textureKey);
		sf::Font* GetFont(std::string Key);

		static ResourcesManager* GetInstance();
	};
}