#include "../include/SandSimulator.h"

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
    m_selectionType = 1;

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


    m_tileSelector.setOutlineThickness(1);
    m_tileSelector.setOutlineColor(sf::Color::White);
    m_tileSelector.setSize(sf::Vector2f(m_gridSizeF, m_gridSizeF));
    m_tileSelector.setFillColor(sf::Color::Transparent);

    m_sand.shape.setSize(sf::Vector2f(m_gridSizeF, m_gridSizeF));
    m_water.shape.setSize(sf::Vector2f(m_gridSizeF, m_gridSizeF));
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
                m_sand.shape.setPosition(x * m_gridSizeF, y * m_gridSizeF);
                m_sand.shape.setFillColor(randomiseColor());
                target.draw(m_sand.shape);
            }
            if(m_currentMap[x][y] == 2)
            {
                m_water.shape.setPosition(x * m_gridSizeF, y * m_gridSizeF);
                m_water.shape.setFillColor(sf::Color::Blue);
                target.draw(m_water.shape);
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
        m_currentMap[m_mousePosGrid->x][m_mousePosGrid->y] = m_selectionType;
    }
    if(sf::Mouse::isButtonPressed(sf::Mouse::Right)&& m_mousePosGrid->x < mapSizeX && m_mousePosGrid->y < mapSizeY)
    {
        //m_currentMap[m_mousePosGrid->x][m_mousePosGrid->y] = 0;
        m_currentMap[m_mousePosGrid->x][m_mousePosGrid->y] = Particles::ParticleType::AIR;
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

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
    {
        m_selectionType = Particles::ParticleType::SAND;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
    {
        m_selectionType = Particles::ParticleType::WATER;
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

    // check if water ABOVE FIRST
    if(y > 0 && m_currentMap[x][y+1] == Particles::ParticleType::WATER)
    {
        m_currentMap[x][y+1] = Particles::ParticleType::SAND;
        m_currentMap[x][y] = Particles::ParticleType::WATER;

    }
    
    if(y < mapSizeY - 1 && m_swapMap[x][y+1] == Particles::ParticleType::AIR)
    {
        m_currentMap[x][y] = Particles::ParticleType::AIR;
        m_currentMap[x][y + 1] = Particles::ParticleType::SAND;

    }
    
    else if(y < mapSizeY - 1 && x > 0 && y > 0 && x < mapSizeX -1 && 
            m_swapMap[x-1][y+1] == Particles::ParticleType::AIR && m_swapMap[x+1][y+1] == Particles::ParticleType::AIR)
    {
        int direction = rand() % 2;
        switch(direction)
        {
            case 0:
                m_currentMap[x][y] = Particles::ParticleType::AIR;
                m_currentMap[x-1][y+1] = Particles::ParticleType::SAND;
                break;
            case 1:
                m_currentMap[x][y] = Particles::ParticleType::AIR;
                m_currentMap[x+1][y+1] = Particles::ParticleType::SAND;
                break;
            default:
                break;

        }
    }
    else if(x > 0 && m_swapMap[x-1][y+1] == Particles::ParticleType::AIR)
    {
        m_currentMap[x][y] = Particles::ParticleType::AIR;
        m_currentMap[x-1][y+1] = Particles::ParticleType::SAND;
    }
    else if(x < mapSizeX - 1 && m_currentMap[x+1][y+1] == Particles::ParticleType::AIR)
    {
        m_currentMap[x][y] = Particles::ParticleType::AIR;
        m_currentMap[x+1][y+1] = Particles::ParticleType::SAND;
    }

}

void SandSimulator::moveWater(long unsigned int &x,  long unsigned int &y)
{
    // check surroundings
    if(y < mapSizeY - 1 && m_swapMap[x][y+1] == Particles::ParticleType::AIR)
    {
        m_currentMap[x][y] = Particles::ParticleType::AIR;
        m_currentMap[x][y + 1] = Particles::ParticleType::WATER;

    }
    
    if(y < mapSizeY - 1 && x > 0 && y > 0 && x < mapSizeX -1 && 
            m_swapMap[x-1][y+1] == Particles::ParticleType::AIR && m_swapMap[x+1][y+1] == Particles::ParticleType::AIR)
    {
        int direction = rand() % 2;
        switch(direction)
        {
            case 0:
                m_currentMap[x][y] = Particles::ParticleType::AIR;
                m_currentMap[x-1][y+1] = Particles::ParticleType::WATER;
                break;
            case 1:
                m_currentMap[x][y] = Particles::ParticleType::AIR;
                m_currentMap[x+1][y+1] = Particles::ParticleType::WATER;
                break;
            default:
                break;

        }
    }
    else if(x > 0 && m_swapMap[x-1][y+1] == Particles::ParticleType::AIR)
    {
        m_currentMap[x][y] = Particles::ParticleType::AIR;
        m_currentMap[x-1][y+1] = Particles::ParticleType::WATER;
    }
    else if(x < mapSizeX - 1 && m_currentMap[x+1][y+1] == Particles::ParticleType::AIR)
    {
        m_currentMap[x][y] = Particles::ParticleType::AIR;
        m_currentMap[x+1][y+1] = Particles::ParticleType::WATER;
    }
    else if(x < mapSizeX - 1 && m_currentMap[x+1][y] == Particles::ParticleType::AIR)
    {
        m_currentMap[x][y] = Particles::ParticleType::AIR;
        m_currentMap[x+1][y] = Particles::ParticleType::WATER;
    }
    else if(x > 0 && m_currentMap[x-1][y] == Particles::ParticleType::AIR)
    {
        m_currentMap[x][y] = Particles::ParticleType::AIR;
        m_currentMap[x-1][y] = Particles::ParticleType::WATER;
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
                switch (m_swapMap[x][y]) 
                {
                    case Particles::ParticleType::AIR:
                        break;
                    case Particles::ParticleType::SAND:
                        moveSand(x,y);
                        break;
                    case Particles::ParticleType::WATER:
                        moveWater(x,y);
                        break;
                    default:
                        break;
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

