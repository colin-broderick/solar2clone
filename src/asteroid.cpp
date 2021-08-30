#include <iostream>
#include <cmath>

#include "asteroid.hpp"
#include "config.hpp"

Solar::Asteroid::Asteroid(const double x_pos, const double y_pos, const double mass)
{
    this->position = sf::Vector2<double>{x_pos, y_pos};
    this->velocity = sf::Vector2<double>{0.0, 0.0};
    this->mass = mass;
    this->radius = 20;
}

void Solar::Asteroid::change_velocity(sf::Vector2<double> delta_velocity)
{
    auto l_velocity = this->velocity + delta_velocity;
    this->velocity = bounded_velocity(l_velocity);
}

void Solar::Asteroid::update_velocity(const std::vector<Solar::Asteroid>& l_asteroids, const double dt)
{
    for (auto& roid2 : l_asteroids)
    {
        if (this != &roid2)
        {
            sf::Vector2<double> sep = (this->getPosition() - roid2.getPosition());
            double distance = std::sqrt(sep.x*sep.x + sep.y*sep.y);
            sf::Vector2<double> force = -GRAVITY * this->getMass() * roid2.getMass() / distance /distance/distance* sep;
            sf::Vector2<double> new_vel = this->velocity + force * dt / this->getMass();
            this->velocity = bounded_velocity(new_vel);

        }
    }
}

const bool Solar::Asteroid::collides(const Solar::Asteroid& other_asteroid) const
{
    double min_sqdist = this->radius + other_asteroid.radius;
    min_sqdist *= min_sqdist;
    double x_del = this->getX() - other_asteroid.getX();
    double y_del = this->getY() - other_asteroid.getY();
    double sqdist = x_del*x_del + y_del*y_del;
    if (sqdist < min_sqdist)
    {
        return true;
    }
    else
    {
        return false;
    }
}

sf::Vector2<double> Solar::Asteroid::bounded_velocity(sf::Vector2<double> proposed_velocity)
{
    auto vel_square = proposed_velocity.x*proposed_velocity.x + proposed_velocity.y*proposed_velocity.y;
    if (vel_square > Asteroid::MaxVelSquare)
    {
        return proposed_velocity * static_cast<double>(Asteroid::MaxVelSquare) / vel_square;
    }
    else
    {
        return proposed_velocity;
    }
}

#if DEBUG == 1
std::ostream& operator<<(std::ostream& stream, const Solar::Asteroid& asteroid)
{
    stream << "Asteroid: Position(" << asteroid.getX() << ", "<< asteroid.getY() << ")" << " Mass(" << asteroid.getMass() << ")";
    return stream;
}
#endif
