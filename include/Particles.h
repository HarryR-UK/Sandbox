#ifndef PARTICLES_H
#define PARTICLES_H
#include "SFML/Graphics/RectangleShape.hpp"
#pragma once

#include <SFML/Graphics.hpp>

namespace Particles{
    
    struct Sand
    {
        sf::RectangleShape shape;
        float m_mass = 0.02f;
    };

    struct Water
    {
        sf::RectangleShape shape;
        float m_mass = 0.05f;
    };
    struct Stone
    {
        sf::RectangleShape shape;
        float m_mass = 1.f;
    };



    enum ParticleType
    {
        AIR = 0,
        SAND = 1,
        WATER = 2,
        STONE = 3

    };
};

#endif
