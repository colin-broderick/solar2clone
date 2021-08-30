#ifndef _CB_SOLAR_BODY_HPP
#define _CB_SOLAR_BODY_HPP

#include "entity.hpp"

namespace Solar
{
    class Body : public Entity
    {
        public:
            double mass;
            double radius;

        public:
            const double getMass() const;
            const double getRadius() const;
    };
}

#endif
