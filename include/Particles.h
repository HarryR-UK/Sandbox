#ifndef PARTICLES_H
#define PARTICLES_H
#include "SFML/Graphics/RectangleShape.hpp"
#pragma once

#include <SFML/Graphics.hpp>

namespace Particles{
    
    struct Sand
    {
        sf::RectangleShape m_shape;
        float m_mass = 0.2f;
    };

    struct Stone
    {
        sf::RectangleShape m_shape;
        float m_mass = 1.f;
    };
};

#endif
