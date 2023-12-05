#include "OhorodnytskyiEngine/Managers/ResourcesManager.h"


namespace OhorodnytskyiEngine
{
    bool ResourcesManager::AddTextureFromFile(std::string filePath, std::string textureKey)
    {
        sf::Texture texture;
        if (texture.loadFromFile(filePath))
        {
            _textures.insert({ textureKey, texture });
            return true;
        }

        return false;
    }

    bool ResourcesManager::AddFontFromFile(std::string filePath, std::string fontKey)
    {
        sf::Font font;
        if (font.loadFromFile(filePath))
        {
            _fonts.insert({ fontKey, font });
            return true;
        }

        return false;
    }

    sf::Texture* ResourcesManager::GetTexture(std::string textureKey)
    {
        return &_textures[textureKey];
    }

    sf::Font* ResourcesManager::GetFont(std::string fontKey)
    {
        return &_fonts[fontKey];
    }

    ResourcesManager* ResourcesManager::resourcesManager_ = nullptr;

    ResourcesManager* ResourcesManager::GetInstance()
    {
        if (resourcesManager_ == nullptr)
        {
            resourcesManager_ = new ResourcesManager();
        }

        return resourcesManager_;
    }

}