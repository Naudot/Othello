#include "Window.h"
#include "Game.h"

Window::Window(Game *game, sf::RenderTarget &render) : m_game(game), m_render(render) 
{
}

Window::~Window()
{
}

void Window::update(const sf::Time &elapsedTime)
{
}

void Window::onEvent(const sf::Event &event)
{
}

void Window::draw()
{
}

sf::RenderTarget &Window::getRender() const
{
	return m_render;
}

sf::RenderWindow const &Window::getRenderWindow() const
{
	return m_game->getRenderWindow();
}

Resources const &Window::getResources() const
{
	return m_game->getResources();
}

bool Window::isFocused() const
{
	return m_game->isFocused();
}

sf::Vector2u const &Window::getSize() const
{
	return m_game->getSize();
}