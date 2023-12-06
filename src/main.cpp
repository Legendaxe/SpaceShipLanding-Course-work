#include "DEFINES/defines.h"
#include <SFML/Graphics.hpp>
#include "OhorodnytskyiEngine/Systems/Game.h"
#include "OhorodnytskyiEngine/Entities/Ship.h"
#include "OhorodnytskyiEngine/Managers/ResourcesManager.h"

void SetupLandingPlace(sf::Sprite* landingPlace);
void SetupResourcesManager();

void HandleInput(sf::RenderWindow& window, sf::Event& event, OhorodnytskyiEngine::Ship& ship);

int main()
{
    SetupResourcesManager();

    sf::Sprite landingPlace;
    SetupLandingPlace(&landingPlace);

    const float fps = 60.0f;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Course Work");

    sf::Clock clock;
    sf::Clock gameTime;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time timePerFrame = sf::seconds(1.f / fps);
    bool redraw = true;

    OhorodnytskyiEngine::Ship ship;

    ship.AddMovementModifier({ "gravity", {0, 1} });
    ship.setPosition({ WINDOW_WIDTH - 400, WINDOW_HEIGHT - 600 });



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

            HandleInput(window, event , ship);
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

void HandleInput(sf::RenderWindow& window, sf::Event& event, OhorodnytskyiEngine::Ship& ship)
{
    while (window.pollEvent(event))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            ship.StartEngine();
        }
        else
        {
            ship.StopEngine();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            ship.rotate(-ROTATE_ANGLE);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            ship.rotate(ROTATE_ANGLE);
        }

        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void SetupResourcesManager()
{
    OhorodnytskyiEngine::ResourcesManager* resourcesManager = OhorodnytskyiEngine::ResourcesManager::GetInstance();
    resourcesManager->AddTextureFromFile("Resources/Ship.png", "ship");
    resourcesManager->AddTextureFromFile("Resources/Landing_place.png", "landing_place");
    resourcesManager->AddTextureFromFile("Resources/Honk.png", "honk");
    resourcesManager->AddFontFromFile("Resources/arial.ttf", "arial");
}

void SetupLandingPlace(sf::Sprite* landingPlace)
{
    sf::Texture* texture = OhorodnytskyiEngine::ResourcesManager::GetInstance()->GetTexture("landing_place");

    landingPlace->setTexture(*texture);
    landingPlace->setPosition(WINDOW_WIDTH - 450, WINDOW_HEIGHT - 20);

    OhorodnytskyiEngine::Game::s_drawableEntities.push_back(landingPlace);
    OhorodnytskyiEngine::Game::s_collidableEntities.push_back(landingPlace);
}