#ifndef _CB_SOLAR_ASTEROID_HPP
#define _CB_SOLAR_ASTEROID_HPP

#include "body.hpp"

namespace Solar
{
    class Asteroid : public Body
    {
        public:
            const static int MaxVelSquare = 1000*1000;
            Asteroid() = delete;
            Asteroid(const double x_pos, const double y_pos, const double mass);
            void change_velocity(sf::Vector2<double> delta_velocity);
            void update_velocity(const std::vector<Solar::Asteroid>& l_asteroids, const double dt);
            const bool collides(const Solar::Asteroid& other_asteroid) const;

        private:
            sf::Vector2<double> bounded_velocity(sf::Vector2<double> proposed_velocity);
    };
}

#if DEBUG == 1
std::ostream& operator<<(std::ostream& stream, const Solar::Asteroid& asteroid);
#endif

#endif
