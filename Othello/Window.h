#pragma once

#include <SFML/Graphics.hpp>
#include "Resources.h"

class Game;

class Window
{
public:
	Window(Game *game, sf::RenderTarget &render);
	~Window();

	virtual void update(const sf::Time &elapsedTime);
	virtual void onEvent(const sf::Event &event);
	virtual void draw();

protected:
	sf::RenderTarget &getRender() const;
	sf::RenderWindow const &getRenderWindow() const;
	Resources const &getResources() const;
	bool isFocused() const;
	sf::Vector2u const &getSize() const;

private:
	Game *m_game;
	sf::RenderTarget &m_render;
};