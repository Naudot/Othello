#pragma once

#include "GameWindow.h"

class MultiGameWindow : public GameWindow
{
public:
	MultiGameWindow(Game *game, sf::RenderTarget &render);
	
protected:
	virtual void onFieldClick(sf::Vector2i location);
};
