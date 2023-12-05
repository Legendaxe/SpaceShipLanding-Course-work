#include "DEFINES/defines.h"
#include <SFML/Graphics.hpp>
#include "OhorodnytskyiEngine/Systems/Game.h"
#include "OhorodnytskyiEngine/Entities/Ship.h"



void HandleInput(sf::RenderWindow& window, sf::Event& event, OhorodnytskyiEngine::Ship& ship);

int main()
{
    const float fps = 60.0f;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");

    sf::Texture landingPlaceTexture;
    landingPlaceTexture.loadFromFile("Resources/Landing_place.png");

    sf::Sprite landingPlace(landingPlaceTexture);
    landingPlace.setPosition(WINDOW_WIDTH - 450, WINDOW_HEIGHT - 20);

    OhorodnytskyiEngine::Game::s_drawableEntities.push_back(&landingPlace);
    OhorodnytskyiEngine::Game::s_collidableEntities.push_back(&landingPlace);

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