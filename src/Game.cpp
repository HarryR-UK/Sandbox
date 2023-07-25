#include "../include/Game.h"

const bool Game::isRunning() const
{
    return m_window->isOpen();
}

Game::~Game()
{
    delete m_window;
}


Game::Game()
    : WINDOW_WIDTH(sf::VideoMode::getDesktopMode().width / 1.2), 
    WINDOW_HEIGHT(sf::VideoMode::getDesktopMode().height / 1.2),
    m_sandSim()
{
    initVariables();
    initWindow();
    initFont();
    initText();

    m_window->setMouseCursorVisible(false);
    m_sandSim.setWindow(*m_window);

    m_gridSizeF = m_sandSim.getGridSizeF();
    initBoundaries();


    startGLoop();

}


void Game::initVariables()
{
    m_simDelay = 11111;
    m_window = nullptr;
    

    m_screenWidth = sf::VideoMode::getDesktopMode().width;
    m_screenHeight = sf::VideoMode::getDesktopMode().height;



}

void Game::initBoundaries()
{

    m_boundaryRight.setSize(sf::Vector2f(10, mapSizeY * m_gridSizeF));
    m_boundaryRight.setPosition(sf::Vector2f(mapSizeX * m_gridSizeF + 1, m_window->getSize().y - m_boundaryRight.getSize().y));
    m_boundaryRight.setFillColor(sf::Color(192,192,192));


}

void Game::initWindow()
{
    m_videoMode.height = WINDOW_HEIGHT;
    m_videoMode.width = WINDOW_WIDTH;

    m_window = new sf::RenderWindow(m_videoMode, "GAME OF LIFE!", sf::Style::Close | sf::Style::None);



}

void Game::initFont()
{
}

void Game::initText()
{

}


void Game::pollEvents()
{
    while(m_window->pollEvent(m_event))
    {
        switch (m_event.type) {
            case sf::Event::Closed:
                m_window->close();
                break;
            default:
                break;
        }
    }

    if(m_window->hasFocus())
    {
        m_window->setMouseCursorVisible(false);
    }
    else{
        m_window->setMouseCursorVisible(true);
    }
}


void Game::getInput()
{

}


void Game::update()
{

    pollEvents();
    if(m_window->hasFocus())
        getInput();

    
    m_sandSim.update(Time::deltaTime,m_simDelay);

}

void Game::renderBoundaries(sf::RenderTarget &target)
{
    target.draw(m_boundaryRight);
}

void Game::render()
{
    //while(isRunning())
    //{
        m_window->clear();

        renderBoundaries(*this->m_window);
        m_sandSim.render(*this->m_window);

        m_sandSim.renderUI(*this->m_window);
        m_window->display();

    //}
}

void Game::updateMousePos()
{
    m_mousePosScreen = sf::Mouse::getPosition();
    m_mousePosWindow = sf::Mouse::getPosition(*m_window);
    m_mousePosView = m_window->mapPixelToCoords(m_mousePosWindow);

    if(m_mousePosView.x >= 0.f)
        m_mousePosGrid.x = m_mousePosView.x / static_cast<unsigned>(m_gridSizeF);

    if(m_mousePosView.y >= 0.f)
        m_mousePosGrid.y = m_mousePosView.y / static_cast<unsigned>(m_gridSizeF);


}


void Game::startGLoop()
{
    m_sandSim.startSimThread();
    m_sandSim.setMousePosGrid(m_mousePosGrid);
    //m_renderThread = std::thread(&Game::render, this);
    while(this->isRunning())
    {
        Time::initDeltaTime();
        this->updateMousePos();
        
        this->update();

        
        this->render();


    }
    m_sandSim.joinSimThread();
    //m_renderThread.join();
}
