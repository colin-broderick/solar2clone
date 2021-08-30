#include "config.hpp"
#include "entity.hpp"

const double Solar::Entity::getX() const
{
    return this->position.x;
}

const double Solar::Entity::getY() const
{
    return this->position.y;
}

const sf::Vector2<double> Solar::Entity::getPosition() const
{
    return this->position;
}

#if DEBUG == 1
std::ostream& operator<<(std::ostream& stream, const Solar::Entity& entity)
{
    stream << "Entity: (" << entity.getX() << ", "<< entity.getY() << ")";
    return stream;
}
#endif
