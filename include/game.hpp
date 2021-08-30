#ifndef _CB_SOLAR_GAME_HPP
#define _CB_SOLAR_GAME_HPP

#include <vector>

#include "config.hpp"
#include "asteroid.hpp"

namespace Solar
{
    class Game
    {
        public:
            Game() = default;
            Game(int id);
            void update(double dt);
            void draw(sf::RenderWindow& window);
            const int body_count() const;
            void add_asteroid(sf::Event::MouseButtonEvent event);
            void add_asteroid(sf::Vector2<double> l_position, sf::Vector2<double> l_velocity);
            Solar::Asteroid* player;

        private:
            enum class GameStates { LOADING, MAIN_MENU, RUNTIME, OPTIONS, GAME_OVER};
            std::vector<Solar::Asteroid> asteroids;
            std::vector<sf::CircleShape> circles;

    };
}

#endif
