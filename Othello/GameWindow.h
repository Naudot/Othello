#pragma once

#include "Window.h"
#include "Field.h"

class GameWindow : public Window
{
public:
	GameWindow(Game *game, sf::RenderTarget &render);

	virtual void update(const sf::Time &elapsedTime);
	virtual void onEvent(const sf::Event &event);
	virtual void draw();

protected:
	Field &getField();
	void setField(int x, int y, FieldShape shape);
	
	FieldShape m_player;
	FieldShape getPlayer() const;
	bool isPlayerTurn() const;
	void setPlayerTurn(bool player);
	void setWinner(FieldShape winner);
	void setError();
	void setCanNotPlay(FieldShape player);

	virtual void onFieldClick(sf::Vector2i location);
	
private:
	void onMouseDown(sf::Vector2i mouse);
	void onMouseUp(sf::Vector2i mouse);
	void drawShapes();
	void drawCursorShape();
	void drawWinner();
	void drawError();
	void drawCanNotPlay(FieldShape player);

	bool m_isError;
	bool m_canNotPlay;
	bool m_isPlayerTurn;

	bool m_finished;
	FieldShape m_winner;
	FieldShape m_playerCanNotPlay;
	sf::Time m_winTime;

	Field m_field;
	sf::Vector2i m_clickedLocation;
};
