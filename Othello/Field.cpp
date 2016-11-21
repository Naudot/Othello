#include "Field.h"
#include <list>

Field::Field()
{
	reset();
}

void Field::reset()
{
	for (int i(0); i < Field::Width; ++i)
		for (int j(0); j < Field::Height; ++j)
			m_field[i][j] = EMPTY;

	set(3, 3, WHITE, false);
	set(4, 3, BLACK, false);
	set(3, 4, BLACK, false);
	set(4, 4, WHITE, false);
}

FieldShape Field::togglePlayer(FieldShape player)
{
	return player == BLACK ? WHITE : BLACK;
}

FieldShape Field::get(int x, int y) const
{
	if (isOutOfBounds(x, y))
		return EMPTY;
	return m_field[x][y];
}

FieldError Field::set(int x, int y, FieldShape shape, bool isChanging)
{
	if (isOutOfBounds(x, y))
		return OUT_OF_BOUNDS;
	if (shape != EMPTY && m_field[x][y] != EMPTY && !isChanging)
		return ALREADY_SET;
	m_field[x][y] = shape;
	return SUCCESS;
}

bool Field::isOutOfBounds(int x, int y) const
{
	if (x < 0 || y < 0 || x > Field::Width || y > Field::Height)
		return true;
	return false;
}

FieldShape Field::getWinner() const
{
	int m_nbBlack = 0;
	int m_nbWhite = 0;

	for (int i(0); i < Field::Width; ++i)
		for (int j(0); j < Field::Height; ++j)
		{
			if (m_field[i][j] == BLACK)
				m_nbBlack++;
			else if (m_field[i][j] == WHITE)
				m_nbWhite++;
		}

	if (m_nbBlack == m_nbWhite)
		return TIE;

	return (m_nbBlack > m_nbWhite ? BLACK : WHITE);
}

bool Field::isFull() const
{
	for (int i(0); i < Field::Width; ++i)
		for (int j(0); j < Field::Height; ++j)
			if (m_field[i][j] == EMPTY)
				return false;
	return true;
}

#pragma region Parsing

bool Field::checkUp(FieldShape player, int x, int y, bool isReversing)
{
	FieldShape actualShape = player == TIE ? m_field[x][y] : player;
	int m_toChange = 0;
	bool m_canChange = false;

	// Evitons les checks inutiles.
	if (y < 2 || actualShape == m_field[x][y - 1])
		return false;

	// Verifie si l'on peut changer les pions tout en donnant le nombre de pions changés.
	// Plus le y tends vers 7 plus le nombre de boucles est grand.
	for (int i(1); i <= y; i++)
	{
		if (actualShape == m_field[x][y - i])
			m_canChange = true;
		if (m_field[x][y - i] == EMPTY || m_canChange)
			break;
		m_toChange++;
	}

	// Change le nombre de pions défini.
	if (isReversing && m_canChange)
		for (int j(0); j <= m_toChange; ++j)
			set(x, y - j, actualShape, true);

	return m_canChange;
}

bool Field::checkDown(FieldShape player, int x, int y, bool isReversing)
{
	FieldShape actualShape = player == TIE ? m_field[x][y] : player;
	int m_toChange = 0;
	bool m_canChange = false;

	if (y > 5 || actualShape == m_field[x][y + 1])
		return false;

	for (int i(1); i <= 7 - y; i++)
	{
		if (actualShape == m_field[x][y + i])
			m_canChange = true;
		if (m_field[x][y + i] == EMPTY || m_canChange)
			break;
		m_toChange++;
	}

	if (isReversing && m_canChange)
		for (int j(0); j <= m_toChange; ++j)
			set(x, y + j, actualShape, true);

	return m_canChange;
}

bool Field::checkLeft(FieldShape player, int x, int y, bool isReversing)
{
	FieldShape actualShape = player == TIE ? m_field[x][y] : player;
	int m_toChange = 0;
	bool m_canChange = false;

	if (x < 2 || actualShape == m_field[x - 1][y])
		return false;

	for (int i(1); i <= x; i++)
	{
		if (actualShape == m_field[x - i][y])
			m_canChange = true;
		if (m_field[x - i][y] == EMPTY || m_canChange)
			break;
		m_toChange++;
	}

	if (isReversing && m_canChange)
		for (int j(0); j <= m_toChange; ++j)
			set(x - j, y, actualShape, true);

	return m_canChange;
}

bool Field::checkRight(FieldShape player, int x, int y, bool isReversing)
{
	FieldShape actualShape = player == TIE ? m_field[x][y] : player;
	int m_toChange = 0;
	bool m_canChange = false;

	if (x > 5 || actualShape == m_field[x + 1][y])
		return false;

	for (int i(1); i <= 7 - x; i++)
	{
		if (actualShape == m_field[x + i][y])
			m_canChange = true;
		if (m_field[x + i][y] == EMPTY || m_canChange)
			break;
		m_toChange++;
	}

	if (isReversing && m_canChange)
		for (int j(0); j <= m_toChange; ++j)
			set(x + j, y, actualShape, true);
	
	return m_canChange;
}

	bool Field::checkUpLeft(FieldShape player, int x, int y, bool isReversing)
{
	FieldShape actualShape = player == TIE ? m_field[x][y] : player;
	int m_toChange = 0;
	bool m_canChange = false;

	if (x == 0 || y == 0 || actualShape == m_field[x - 1][y - 1])
		return false;

	int diag = x < y ? x : y;

	for (int i(1); i <= diag; i++)
	{
		if (actualShape == m_field[x - i][y - i])
			m_canChange = true;
		if (m_field[x - i][y - i] == EMPTY || m_canChange)
			break;
		m_toChange++;
	}

	if (isReversing && m_canChange)
		for (int j(0); j <= m_toChange; ++j)
			set(x - j, y - j, actualShape, true);
	
	return m_canChange;
}

bool Field::checkUpRight(FieldShape player, int x, int y, bool isReversing)
{
	FieldShape actualShape = player == TIE ? m_field[x][y] : player;
	int m_toChange = 0;
	bool m_canChange = false;

	if (x == 7 || y == 0 || actualShape == m_field[x + 1][y - 1])
		return false;

	int diag = 7 - x < y ? 7 - x : y;

	for (int i(1); i <= diag; i++)
	{
		if (actualShape == m_field[x + i][y - i])
			m_canChange = true;
		if (m_field[x + i][y - i] == EMPTY || m_canChange)
			break;
		m_toChange++;
	}

	if (isReversing && m_canChange)
		for (int j(0); j <= m_toChange; ++j)
			set(x + j, y - j, actualShape, true);
	
	return m_canChange;
}

bool Field::checkDownLeft(FieldShape player, int x, int y, bool isReversing)
{
	FieldShape actualShape = player == TIE ? m_field[x][y] : player;
	int m_toChange = 0;
	bool m_canChange = false;

	if (x == 0 || y == 7 || actualShape == m_field[x - 1][y + 1])
		return false;

	int diag = x < 7 - y ? x : 7 - y;

	for (int i(1); i <= diag; i++)
	{
		if (actualShape == m_field[x - i][y + i])
			m_canChange = true;
		if (m_field[x - i][y + i] == EMPTY || m_canChange)
			break;
		m_toChange++;
	}

	if (isReversing && m_canChange)
		for (int j(0); j <= m_toChange; ++j)
			set(x - j, y + j, actualShape, true);
	
	return m_canChange;
}

bool Field::checkDownRight(FieldShape player, int x, int y, bool isReversing)
{
	FieldShape actualShape = player == TIE ? m_field[x][y] : player;
	int m_toChange = 0;
	bool m_canChange = false;

	if (x == 7 || y == 7 || actualShape == m_field[x + 1][y + 1])
		return false;

	int diag = 7 - x < 7 - y ? 7 - x : 7 - y;

	for (int i(1); i <= diag; i++)
	{
		if (actualShape == m_field[x + i][y + i])
			m_canChange = true;
		if (m_field[x + i][y + i] == EMPTY || m_canChange)
			break;
		m_toChange++;
	}

	if (isReversing && m_canChange)
		for (int j(0); j <= m_toChange; ++j)
			set(x + j, y + j, actualShape, true);
	
	return m_canChange;
}
#pragma endregion Parsing

bool Field::checkAll(FieldShape player, int x, int y, bool isReversing)
{
	bool m_checked = 
	checkUp(player, x,y, isReversing) ||
	checkDown(player,x,y, isReversing) ||
	checkLeft(player,x,y, isReversing) ||
	checkRight(player,x,y, isReversing) ||
	checkUpLeft(player,x,y, isReversing) ||
	checkUpRight(player,x,y, isReversing) ||
	checkDownLeft(player,x,y, isReversing) ||
	checkDownRight(player,x,y, isReversing);

	return m_checked;
}

bool Field::canSet(int x, int y)
{
	return checkAll(TIE, x,y,false);
}

bool Field::canPlay(FieldShape player)
{
	bool m_canPlay = false;

	for (int i(0); i < Field::Width; ++i)
	{
		for (int j(0); j < Field::Height; ++j)
		{
			if (m_field[i][j] == EMPTY)
				m_canPlay = checkAll(player, i,j,false);
			if (m_canPlay)
				return true;
		}
	}
	return m_canPlay;
}