#ifndef SANDSIMULATOR_H
#define SANDSIMULATOR_H
#pragma once

#include <array>
#include <thread>
#include <iostream>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Global.h"
#include "Particles.h"
#include "Time.h"

constexpr int mapSizeX = MAP_SIZE_X;
constexpr int mapSizeY = MAP_SIZE_Y;

class SandSimulator
{
    private:
        void initVariables();
        void initGrid();
        void initText();

        bool m_isHeld;

        // GRID
        float m_gridSizeF;
        unsigned m_gridSizeU;
        
        unsigned long int m_currentMap[mapSizeX][mapSizeY];
        unsigned long int m_swapMap[mapSizeX][mapSizeY];

        // Particles
        // 1
        Particles::Sand m_sand;
        // 2
        Particles::Water m_water;

        sf::RenderWindow* m_window;
        
        sf::Vector2u* m_mousePosGrid;

        std::thread m_simThread;

        sf::RectangleShape m_tileSelector;

        int m_selectionType;


        int m_simDelay;
        sf::Color m_randomColor;

        // UI
        sf::Font m_font;

    public:
        SandSimulator();
        virtual ~SandSimulator();

        void update(float deltaTime, int simDelay);
        void updateTileSelector();

        void getInput();

        void startSimThread();
        void joinSimThread();

        void render(sf::RenderTarget &target);
        void renderUI(sf::RenderTarget &target);
        
        void simulate();

        float getGridSizeF();

        void setWindow(sf::RenderWindow &window);
        void setMousePosGrid(sf::Vector2u &mousePosGrid);

        void resetGrid();

        void moveSand(long unsigned int &x, long unsigned int &y);
        void moveWater(long unsigned int &x, long unsigned int &y);

        sf::Color randomiseColor();
        

};

#endif
