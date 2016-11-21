#pragma once

enum FieldShape
{
	EMPTY = 0,
	BLACK = 1,
	WHITE = 2,
	TIE = 3
};

enum FieldError
{
	SUCCESS = 0,
	ALREADY_SET = 1,
	OUT_OF_BOUNDS = 2,
	CAN_NOT_TAKE = 3
};

class Field
{
public:
	Field();
	void reset();
	FieldShape togglePlayer(FieldShape player);

	FieldShape get(int x, int y) const;
	FieldError set(int x, int y, FieldShape shape, bool isChanging);
	FieldShape getWinner() const;
	bool isFull() const;
	bool isOutOfBounds(int x, int y) const;

	static const int Width = 8;
	static const int Height = 8;
	
	bool Field::checkUp(FieldShape player, int x, int y, bool isReversing);
	bool Field::checkDown(FieldShape player,int x, int y, bool isReversing);
	bool Field::checkLeft(FieldShape player,int x, int y, bool isReversing);
	bool Field::checkRight(FieldShape player,int x, int y, bool isReversing);
	bool Field::checkUpLeft(FieldShape player,int x, int y, bool isReversing);
	bool Field::checkUpRight(FieldShape player,int x, int y, bool isReversing);
	bool Field::checkDownLeft(FieldShape player,int x, int y, bool isReversing);
	bool Field::checkDownRight(FieldShape player,int x, int y, bool isReversing);

	bool Field::checkAll(FieldShape player,int x, int y, bool isReversing);

	bool Field::canSet(int x, int y);
	bool Field::canPlay(FieldShape player);

private:
	FieldShape m_field[8][8];
};