#pragma once

#include <SFML/Graphics.hpp>
#include "Resources.h"
#include "Window.h"

class Game
{
public:
	Game();
	~Game();
	void start();

	sf::RenderWindow const &getRenderWindow() const;

	void setSize(sf::Vector2u);
	sf::Vector2u const &getSize() const;

	Resources const &getResources() const;
	bool isFocused() const;

private:
	void update();
	void draw();

	Window *m_gameWindow;
	sf::RenderWindow m_renderWindow;

	sf::Vector2u m_windowSize;
	
	Resources m_resources;
	bool m_focused;
	
	sf::Time m_elapsedTime;
};