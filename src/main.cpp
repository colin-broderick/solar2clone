#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <thread>

#include "game.hpp"
#include "config.hpp"
#include "asteroid.hpp"

int main(int argc, char* argv[])
{
    // Create default game object.
    Solar::Game game{0};

    // Create and configure render window.
    sf::RenderWindow window{{800, 600}, "SolarClone"};
    window.setFramerateLimit(FRAME_RATE_LIMIT);

    // Start the SFML clock, to provide dt.
    sf::Clock deltaClock;
    double dt;

    sf::Vector2<double> mDown;
    sf::Vector2<double> mUp;

    sf::View camera{{0, 0, 800, 600}};

    // Start game loop.
    while (window.isOpen())
    {
        // Process events.
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            
            case sf::Event::MouseButtonPressed:
                mDown = {
                    static_cast<double>(event.mouseButton.x),
                    static_cast<double>(event.mouseButton.y)
                };
                mDown -= sf::Vector2<double>(camera.getCenter());
                mDown += {400, 300};
                break;

            case sf::Event::MouseButtonReleased:
                if (game.body_count() < MAX_BODIES)
                {
                    mUp = {
                        static_cast<double>(event.mouseButton.x),
                        static_cast<double>(event.mouseButton.y)
                    };
                    mUp -= sf::Vector2<double>(camera.getCenter());
                    mUp += {400, 300};
                    game.add_asteroid(mDown, mUp - mDown);
                }
                break;
            default:
                break;
            }
        }

        // Calculate dt.
        dt = deltaClock.restart().asSeconds();

        double vel = std::sqrt(game.player->velocity.y*game.player->velocity.y + game.player->velocity.x*game.player->velocity.x);

        // Check player keyboard input.
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            game.player->change_velocity(sf::Vector2<double>{0, -50} * dt);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            game.player->change_velocity(sf::Vector2<double>{0, 50} * dt);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            game.player->change_velocity(sf::Vector2<double>{-50, 0} * dt);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            game.player->change_velocity(sf::Vector2<double>{50, 0} * dt);
        }

        game.update(dt);

        camera.setCenter(game.player->getX(), game.player->getY());
        window.setView(camera);

        game.draw(window);

        window.display();
    }

    return 0;
}
