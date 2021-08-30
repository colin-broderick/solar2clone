#include <cmath>

#include "game.hpp"

Solar::Game::Game(int id)
{
    asteroids.reserve(MAX_BODIES);
    asteroids.emplace_back(Solar::Asteroid{400, 300, 3.33e5});
    // asteroids.emplace_back(Solar::Asteroid{457.7, 300, 1});
    // asteroids.emplace_back(Solar::Asteroid{422.3, 300, 5.5e-2});
    // asteroids.emplace_back(Solar::Asteroid{441.7, 300, 8.15e-1});
    // asteroids.emplace_back(Solar::Asteroid{700, 300, 3.18e2});
    // asteroids.emplace_back(Solar::Asteroid{487.7, 300, 1.07e-1});
    // asteroids[1].velocity = {0, 300};
    // asteroids[0].velocity = {0, 0};
    // asteroids[1].velocity = {0, 227};
    // asteroids[2].velocity = {0, 365};
    // asteroids[3].velocity = {0, 267};
    // asteroids[4].velocity = {0, 100};
    // asteroids[5].velocity = {0, 183};

    player = &(asteroids[0]);

    for (int i = 0; i < asteroids.size(); i++)
    {
        circles.emplace_back(sf::CircleShape{20.0});
    }
}

void Solar::Game::update(double dt)
{
    // Apply velocity damping.
    for (auto& asteroid : asteroids)
    {
        asteroid.velocity *= (1 - VELOCITY_DECAY_FACTOR);
    }

    // Calculate new asteroid velocities.
    for (auto& asteroid : asteroids)
    {
        asteroid.update_velocity(asteroids, dt);
    }

    // Update asteroid positions.
    for (auto& asteroid : asteroids)
    {
        asteroid.position = asteroid.position + asteroid.velocity * dt;
    }

    // Check for collisions.
    for (auto& asteroid1 : asteroids)
    {
        for (auto& asteroid2 : asteroids)
        {
            if (&asteroid1 != &asteroid2)
            {
                if (asteroid1.collides(asteroid2))
                {
                    #define COLLISION_MODE_BOUNCE 1
                    #if COLLISION_MODE_BOUNCE == 1
                    sf::Vector2<double> collision_vector, collision_vector_norm, relative_velocity_vector;
                    double distance, speed, impulse;

                    collision_vector = asteroid2.getPosition() - asteroid1.getPosition();
                    distance = std::sqrt(collision_vector.x*collision_vector.x + collision_vector.y*collision_vector.y);
                    collision_vector_norm = collision_vector / distance;
                    relative_velocity_vector = asteroid1.velocity - asteroid2.velocity;
                    speed = relative_velocity_vector.x*collision_vector_norm.x + relative_velocity_vector.y*collision_vector_norm.y;
                    impulse = 2*speed/(asteroid1.getMass() + asteroid2.getMass());
                    if (speed >= 0)
                    {
                        asteroid1.velocity = asteroid1.velocity - impulse * asteroid2.getMass() * collision_vector_norm;
                        asteroid2.velocity = asteroid2.velocity + impulse * asteroid1.getMass() * collision_vector_norm;
                    }
                    #else

                    #endif
                }
            }
        }
    }
}

void Solar::Game::draw(sf::RenderWindow& window)
{
    for (int i = 0; i < asteroids.size(); i++)
    {
        circles[i].setPosition(asteroids[i].getX(), asteroids[i].getY());
    }

    window.clear();

    for (auto& circ : circles)
    {
        window.draw(circ);
    }
}

const int Solar::Game::body_count() const
{
    return asteroids.size();
}

void Solar::Game::add_asteroid(sf::Event::MouseButtonEvent event)
{
    asteroids.emplace_back(Solar::Asteroid{
        static_cast<double>(event.x),
        static_cast<double>(event.y),
        INITIAL_ASTEROID_MASS
    });
    circles.emplace_back(sf::CircleShape{10.0});
}

void Solar::Game::add_asteroid(sf::Vector2<double> l_position, sf::Vector2<double> l_velocity)
{
    asteroids.emplace_back(Solar::Asteroid{
        l_position.x,
        l_position.y,
        INITIAL_ASTEROID_MASS
    });
    asteroids.back().velocity = l_velocity;
    circles.emplace_back(sf::CircleShape{INITIAL_ASTEROID_MASS/1000.0});
}
