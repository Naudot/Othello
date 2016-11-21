#include <SFML/Graphics.hpp>
#include "GameWindow.h"

GameWindow::GameWindow(Game *game, sf::RenderTarget &render)
	: Window(game, render),
	m_player(BLACK),
	m_isPlayerTurn(false),
	m_finished(false),
	m_isError(false),
	m_canNotPlay(false)
{
	
}

void GameWindow::update(const sf::Time &elapsedTime)
{
	if (m_isError || m_canNotPlay)
	{
		m_winTime -= elapsedTime;
		if (m_winTime.asMilliseconds() < 0)
		{
			m_isError = false;
			m_canNotPlay = false;
		}
	}

	if (m_finished)
	{
		m_winTime -= elapsedTime;
		if (m_winTime.asMilliseconds() < 0)
		{
			m_field.reset();
			m_player = BLACK;
			m_finished = false;
			m_canNotPlay = false;
		}
	}
}

void GameWindow::onEvent(const sf::Event &event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
			onMouseDown(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
	}
	else if (event.type == sf::Event::MouseButtonReleased)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
			onMouseUp(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
	}
}

void GameWindow::draw()
{
	sf::Sprite field(getResources().getTexture("field"));
	getRender().draw(field);
	drawShapes();
	if (m_canNotPlay)
		drawCanNotPlay(m_playerCanNotPlay);
	if (m_isError)
		drawError();
	if (m_finished)
		drawWinner();
	if (!m_finished && m_isPlayerTurn)
		drawCursorShape();
}

Field &GameWindow::getField()
{
	return m_field;
}

void GameWindow::setField(int x, int y, FieldShape actualPlayer)
{
	m_field.checkUp(TIE, x,y, true);
	m_field.checkDown(TIE, x,y, true);
	m_field.checkLeft(TIE, x,y, true);
	m_field.checkRight(TIE, x,y, true);
	m_field.checkUpLeft(TIE, x,y, true);
	m_field.checkUpRight(TIE, x,y, true);
	m_field.checkDownLeft(TIE, x,y, true);
	m_field.checkDownRight(TIE, x,y, true);
}

FieldShape GameWindow::getPlayer() const
{
	return m_player;
}

bool GameWindow::isPlayerTurn() const
{
	return m_isPlayerTurn;
}

void GameWindow::setPlayerTurn(bool player)
{
	m_isPlayerTurn = player;
}

void GameWindow::setWinner(FieldShape winner)
{
	m_finished = true;
	m_winner = winner;
	m_winTime = sf::seconds(5);
}

void GameWindow::setError()
{
	m_isError = true;
	m_winTime = sf::seconds(2);
}

void GameWindow::setCanNotPlay(FieldShape player)
{
	m_canNotPlay = true;
	m_playerCanNotPlay = player;
	m_winTime = sf::seconds(5);
}

void GameWindow::onFieldClick(sf::Vector2i location)
{
}

void GameWindow::onMouseDown(sf::Vector2i mouse)
{
	if (m_finished)
		return;

	int fieldX = mouse.x * 8 / Window::getSize().x;
	int fieldY = mouse.y * 8 / Window::getSize().y;

	m_clickedLocation = sf::Vector2i(fieldX, fieldY);
}

void GameWindow::onMouseUp(sf::Vector2i mouse)
{
	if (m_finished)
		return;

	int fieldX = mouse.x * 8 / Window::getSize().x;
	int fieldY = mouse.y * 8 / Window::getSize().y;

	sf::Vector2i location(fieldX, fieldY);

	if (m_clickedLocation == location)
		onFieldClick(location);
}

void GameWindow::drawShapes()
{
	for (int i(0); i < 9; ++i)
		for (int j(0); j < 9; ++j)
		{
			FieldShape shape = m_field.get(i, j);
			if (shape != EMPTY)
			{
				sf::Sprite sprite;
				if (shape == BLACK)
					sprite.setTexture(getResources().getTexture("black"));
				else
					sprite.setTexture(getResources().getTexture("white"));
				sprite.setPosition(9.0f + i * 75.0f, 9.0f + j * 75.0f);
				getRender().draw(sprite);
			}
		}
}

void GameWindow::drawCursorShape()
{
	if (m_player == EMPTY || !isFocused())
		return;

	sf::Vector2i mouse = sf::Mouse::getPosition(getRenderWindow());
	if (mouse.x < 0 || mouse.y < 0)
		return;

	int fieldX = mouse.x * 8 / Window::getSize().x;
	int fieldY = mouse.y * 8 / Window::getSize().y;

	if (m_field.isOutOfBounds(fieldX, fieldY) || m_field.get(fieldX, fieldY) == m_player)
		return;

	sf::Sprite sprite;
	if (m_player == BLACK)
		sprite.setTexture(getResources().getTexture("black"));
	else
		sprite.setTexture(getResources().getTexture("white"));

	sprite.setPosition(9.0f + fieldX * 75.0f, 9.0f + fieldY * 75.0f);
	sprite.setColor(sf::Color(255, 255, 255, 128));
	getRender().draw(sprite);
}

void GameWindow::drawWinner()
{
	sf::Text text("", getResources().getFont(), 64);

	switch (m_winner)
	{
	case BLACK:
		text.setString("Black wins!");
		break;
	case WHITE:
		text.setString("White wins!");
		break;
	default:
		text.setString("Nobody wins.");
		break;
	}

	sf::FloatRect textSize = text.getLocalBounds();

	text.setColor(sf::Color::Black);
	text.setPosition(sf::Vector2f((600 - textSize.width) / 2, (600 / 2) - textSize.height));

	sf::RectangleShape shape;
	shape.setFillColor(sf::Color(127,221,76));
	shape.setOutlineThickness(2);
	shape.setOutlineColor(sf::Color::Black);
	shape.setSize(sf::Vector2f(textSize.width, textSize.height + 10));
	shape.setPosition(text.getPosition().x , text.getPosition().y);
	
	getRender().draw(shape);
	getRender().draw(text);
}

void GameWindow::drawError()
{
	sf::Text text("You are not able to play here.", getResources().getFont(), 48);

	sf::FloatRect textSize = text.getLocalBounds();

	text.setColor(sf::Color::Black);
	text.setPosition(sf::Vector2f((600 - textSize.width) / 2, (600 / 2) - textSize.height));

	sf::RectangleShape shape;
	// 116	208	241
	shape.setFillColor(sf::Color(127,221,76));
	shape.setOutlineThickness(2);
	shape.setOutlineColor(sf::Color::Black);
	shape.setSize(sf::Vector2f(textSize.width, textSize.height + 10));
	shape.setPosition(text.getPosition().x, text.getPosition().y);
	
	getRender().draw(shape);
	getRender().draw(text);
}

void GameWindow::drawCanNotPlay(FieldShape player)
{
	sf::Text text("", getResources().getFont(), 48);

	switch (player)
	{
	case BLACK:
		text.setString("Black can not play !");
		break;
	case WHITE:
		text.setString("White can not play !");
		break;
	default:
		text.setString("Nobody can play.");
		break;
	}

	sf::FloatRect textSize = text.getLocalBounds();

	text.setColor(sf::Color::Black);
	text.setPosition(sf::Vector2f((600 - textSize.width) / 2, (400 / 2) - textSize.height));

	sf::RectangleShape shape;
	shape.setFillColor(sf::Color(127,221,76));
	shape.setOutlineThickness(2);
	shape.setOutlineColor(sf::Color::Black);
	shape.setSize(sf::Vector2f(textSize.width, textSize.height + 10));
	shape.setPosition(text.getPosition().x, text.getPosition().y);
	
	getRender().draw(shape);
	getRender().draw(text);
}