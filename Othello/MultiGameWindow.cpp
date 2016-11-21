#include "MultiGameWindow.h"

MultiGameWindow::MultiGameWindow(Game *game, sf::RenderTarget &render)
	: GameWindow(game, render)
{
	setPlayerTurn(true);
}

void MultiGameWindow::onFieldClick(sf::Vector2i location)
{
	Field &field = getField();
	if (field.set(location.x, location.y, getPlayer(), false) == SUCCESS)
	{
		if (field.canSet(location.x, location.y))
		{
			setField(location.x, location.y, getPlayer());
			m_player = field.togglePlayer(getPlayer());
		}
		else
		{
			field.set(location.x, location.y, EMPTY, true);
			setError();
		}

		if (!field.canPlay(WHITE) && !field.canPlay(BLACK))
		{
			setCanNotPlay(TIE);
			FieldShape winner = field.getWinner();
			setWinner(winner);
			return;
		}
		else if (getPlayer() == WHITE && !field.canPlay(WHITE))
		{
			setCanNotPlay(WHITE);
			m_player = BLACK;
		}
		else if (getPlayer() == BLACK && !field.canPlay(BLACK))
		{
			setCanNotPlay(BLACK);
			m_player = WHITE;
		}

		if (field.isFull())
		{
			FieldShape winner = field.getWinner();
			setWinner(winner);
		}
	}
}
