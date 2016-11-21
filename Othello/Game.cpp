#include "Game.h"
#include "MultiGameWindow.h"

Game::Game()
{
	m_renderWindow.create(sf::VideoMode(602, 602), "Othello", sf::Style::Titlebar | sf::Style::Close);
	m_renderWindow.setFramerateLimit(60);
	m_resources.load();

	setSize(m_renderWindow.getSize());

	m_gameWindow = new MultiGameWindow(this, m_renderWindow);
}

Game::~Game()
{
	delete m_gameWindow;
}

void Game::start()
{
	sf::Clock clock;
	while (m_renderWindow.isOpen())
	{
		m_elapsedTime = clock.restart();
		update();
		draw();
	}
}

sf::RenderWindow const &Game::getRenderWindow() const
{
	return m_renderWindow;
}

Resources const &Game::getResources() const
{
	return m_resources;
}

bool Game::isFocused() const
{
	return m_focused;
}

void Game::update()
{
	m_gameWindow->update(m_elapsedTime);

	sf::Event event;
	while (m_renderWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_renderWindow.close();
		else if (event.type == sf::Event::GainedFocus)
			m_focused = true;
		else if (event.type == sf::Event::LostFocus)
			m_focused = false;
		else if (m_focused)
			m_gameWindow->onEvent(event);
	}
}

void Game::draw()
{
	m_renderWindow.clear();
	
	m_gameWindow->draw();

	m_renderWindow.display();
}

void Game::setSize(sf::Vector2u size)
{
	m_renderWindow.setSize(size);
	m_windowSize = size;
}

sf::Vector2u const &Game::getSize() const
{
	return m_windowSize;
}