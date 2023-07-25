#include "../include/SandSimulator.h"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"

SandSimulator::~SandSimulator()
{
}
SandSimulator::SandSimulator()
{
    initVariables();
    initText();
    initGrid();
}

void SandSimulator::initVariables()
{
    m_window = nullptr;
    m_simDelay =0;
    m_isHeld = false;

}

void SandSimulator::joinSimThread()
{
    m_simThread.join();
}

void SandSimulator::initText()
{
    if(!m_font.loadFromFile("../res/fonts/open-sans/OpenSans-Semibold.ttf"))
        std::cerr << "ERROR:: CANNOT INIT FONT" << '\n';
}

void SandSimulator::initGrid()
{
    m_gridSizeF = 10.f;
    m_gridSizeU = static_cast<unsigned>(m_gridSizeF);



    resetGrid();


    m_sand.setSize(sf::Vector2f(m_gridSizeF, m_gridSizeF));
    m_tileSelector.setOutlineThickness(1);
    m_tileSelector.setOutlineColor(sf::Color::White);
    m_tileSelector.setSize(sf::Vector2f(m_gridSizeF, m_gridSizeF));
    m_tileSelector.setFillColor(sf::Color::Transparent);
}

void SandSimulator::updateTileSelector()
{
    m_tileSelector.setPosition(m_mousePosGrid->x * m_gridSizeF, m_mousePosGrid->y * m_gridSizeF);
}

void SandSimulator::render(sf::RenderTarget &target)
{
    for(long unsigned int x = 0; x < mapSizeX; ++x)
    {
        for(long unsigned int y = 0; y < mapSizeY; ++y)
        {
            if(m_currentMap[x][y] == 1)
            {

                // NEW SF RECTANGLE HERE
                m_sand.setPosition(x * m_gridSizeF, y * m_gridSizeF);
                m_sand.setFillColor(randomiseColor());
                target.draw(m_sand);
            }

            m_swapMap[x][y] = m_currentMap[x][y];

        }
    }

    target.draw(m_tileSelector);
}

void SandSimulator::renderUI(sf::RenderTarget &target)
{

}

void SandSimulator::getInput()
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_mousePosGrid->x < mapSizeX && m_mousePosGrid->y < mapSizeY)
    {
        //m_currentMap[m_mousePosGrid->x][m_mousePosGrid->y] = 1;
        m_currentMap[m_mousePosGrid->x][m_mousePosGrid->y] = 1;
    }
    if(sf::Mouse::isButtonPressed(sf::Mouse::Right)&& m_mousePosGrid->x < mapSizeX && m_mousePosGrid->y < mapSizeY)
    {
        //m_currentMap[m_mousePosGrid->x][m_mousePosGrid->y] = 0;
        m_currentMap[m_mousePosGrid->x][m_mousePosGrid->y] = 0;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))
    {
        if(!m_isHeld)
        {
            m_isHeld = true;
            resetGrid();
        }
    }
    else{
        m_isHeld = false;
    }
    

}

void SandSimulator::startSimThread()
{
    m_simThread = std::thread(&SandSimulator::simulate, this);
}

void SandSimulator::update(float deltaTime, int simDelay)
{
    m_simDelay = simDelay;
    updateTileSelector();

    if(m_window->hasFocus())
        getInput();
   
    //simulate();

}

void SandSimulator::moveSand(long unsigned int &x, long unsigned int &y)
{

    // check surroundings
    if(y < mapSizeY - 1 && m_swapMap[x][y+1] == 0)
    {
        m_currentMap[x][y] = 0;
        m_currentMap[x][y + 1] = 1;

    }
    else if(y < mapSizeY - 1 && x > 0 && y > 0 && x < mapSizeX -1 && m_swapMap[x-1][y+1] == 0 && m_swapMap[x+1][y+1] == 0)
    {
        int direction = rand() % 2;
        switch(direction)
        {
            case 0:
                m_currentMap[x][y] = 0;
                m_currentMap[x-1][y+1] = 1;
                break;
            case 1:
                m_currentMap[x][y] = 0;
                m_currentMap[x+1][y+1] = 1;
                break;
            default:
                break;

        }
    }
    else if(x > 0 && m_swapMap[x-1][y+1] == 0)
    {
        m_currentMap[x][y] = 0;
        m_currentMap[x-1][y+1] = 1;
    }
    else if(x < mapSizeX - 1 && m_currentMap[x+1][y+1] == 0)
    {
        m_currentMap[x][y] = 0;
        m_currentMap[x+1][y+1] = 1;
    }

}



void SandSimulator::simulate()
{
    while(m_window->isOpen())
    {
        usleep(m_simDelay);
        for(long unsigned int x = 0; x < mapSizeX; ++x)
        {
            for(long unsigned int y = 0; y < mapSizeY -1; ++y)
            {
                if(m_swapMap[x][y] == 1)
                {
                    moveSand(x,y);
                }
            }
        }

    }

    
}

sf::Color SandSimulator::randomiseColor()
{
    int ranColor = rand() % 5;
    switch(ranColor)
    {
        case 0:
            return sf::Color::Yellow;
            break;
        case 1:
            return sf::Color(252,201,0);
            break;
        case 2:
            return sf::Color(168,134,0);
            break;
        case 3:
            return sf::Color(255,224,98);
            break;
        case 4:
            return sf::Color(255,179,0);
            break;
        default:
            return sf::Color::Yellow;
            break;

    }
}

void SandSimulator::setWindow(sf::RenderWindow &window)
{
    m_window = &window;
}

void SandSimulator::setMousePosGrid(sf::Vector2u &mousePosGrid)
{
    m_mousePosGrid = &mousePosGrid;
}

float SandSimulator::getGridSizeF()
{
    return m_gridSizeF;
}

void SandSimulator::resetGrid()
{
    for(long unsigned int x = 0; x < mapSizeX; ++x)
    {
        for(long unsigned int y = 0; y < mapSizeY; ++y)
        {
            m_currentMap[x][y] = 0;
            m_swapMap[x][y] = 0;
        }

    } 
}

