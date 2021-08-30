#ifndef _CB_SOLAR_ENTITY_HPP
#define _CB_SOLAR_ENTITY_HPP

#include <SFML/Graphics.hpp>

#include <iostream>

namespace Solar
{
    class Entity
    {
        public:
            sf::Vector2<double> position;
            sf::Vector2<double> velocity;

        public:
            const double getX() const;
            const double getY() const;
            const sf::Vector2<double> getPosition() const;
    };
}

#if DEBUG == 1
std::ostream& operator<<(std::ostream& stream, const Solar::Entity& entity);
#endif

#endif
