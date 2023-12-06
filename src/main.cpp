#include "DEFINES/defines.h"
#include <SFML/Graphics.hpp>
#include "OhorodnytskyiEngine/Systems/Game.h"
#include "OhorodnytskyiEngine/Entities/Ship.h"
#include "OhorodnytskyiEngine/Managers/ResourcesManager.h"

void SetupResourcesManager();

int main()
{
    SetupResourcesManager();

    const float fps = 60.0f;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Course Work");

    sf::Clock clock;
    sf::Clock gameTime;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time timePerFrame = sf::seconds(1.f / fps);
    bool redraw = true;

    OhorodnytskyiEngine::Game game(window);

    sf::Event event;

    while (window.isOpen())
    {
        if (clock.getElapsedTime() >= timePerFrame)
        {
            redraw = true; 
            game.Tick(gameTime.getElapsedTime());
            clock.restart();
            switch (OhorodnytskyiEngine::Game::s_gameState)
            {
            case OhorodnytskyiEngine::GameState::Losed:
                game.DeclareCompletion(OhorodnytskyiEngine::GameState::Losed);
                return 0;
            case OhorodnytskyiEngine::GameState::Winned:
                game.DeclareCompletion(OhorodnytskyiEngine::GameState::Winned);
                return 0;
            }

            game.HandleInput(event);
        }

        if (redraw)
        {
            redraw = false;
            window.clear(sf::Color::Cyan);
            for (auto sprite : OhorodnytskyiEngine::Game::s_drawableEntities)
            {
                window.draw(*sprite);
            }
            window.display();
        }
    }

    return 0;
}

void SetupResourcesManager()
{
    OhorodnytskyiEngine::ResourcesManager* resourcesManager = OhorodnytskyiEngine::ResourcesManager::GetInstance();
    resourcesManager->AddTextureFromFile("Resources/Ship.png", "ship");
    resourcesManager->AddTextureFromFile("Resources/Landing_place.png", "landing_place");
    resourcesManager->AddTextureFromFile("Resources/Honk.png", "honk");
    resourcesManager->AddFontFromFile("Resources/arial.ttf", "arial");
}