#ifndef GAME_H
#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <thread>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "SandSimulator.h"
#include "Global.h"



class Game
{
    private:
        sf::RenderWindow* m_window;
        sf::VideoMode m_videoMode;



        sf::Event m_event;
        sf::Cursor m_cursor;

        int m_simDelay;


        // Screen Info
        int m_screenWidth;
        int m_screenHeight;

        void initVariables();
        void initWindow();
        void initFont();
        void initText();
        void initGrid();
        void initBoundaries();

        // FONT
        sf::Font m_mainFont;

        std::thread m_renderThread;

        SandSimulator m_sandSim;

        // MOUSE POS
        sf::Vector2i m_mousePosScreen;
        sf::Vector2i m_mousePosWindow;
        sf::Vector2f m_mousePosView;
        sf::Vector2u m_mousePosGrid;
        float m_gridSizeF;

        // BOUNDARIES
        sf::RectangleShape m_boundaryRight;

    public:
        Game();
        virtual ~Game();

        void startGLoop();

        void update();
        void updateTileSelector();
        void updateMousePos();

        void pollEvents();
        void getInput();

        void render();
        void renderBoundaries(sf::RenderTarget &target);


        const bool isRunning() const;

        const int WINDOW_WIDTH;
        const int WINDOW_HEIGHT;

        // Accessors
        sf::RenderWindow* getWindow();


};


#endif
