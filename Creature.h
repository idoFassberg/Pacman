#pragma once
#include "Board.h"

enum Direction { UP, DOWN, LEFT, RIGHT, STAY};

class Creature {

private:

	int m_row;
	int m_col;
	Direction m_dir;

protected: //so the creatures (pacman, ghost ,etc..) will have acsees to board

	Board& m_board;

public:

	//Getters
	int getRow()const { return m_row; }
	int getCol()const { return m_col; }
	Direction getDir()const { return (Direction)m_dir; }
	Board& getBoard() { return m_board; }

	//Setters
	void setRow(const int& x) { m_row = x; }
	void setCol(const int& y) { m_col = y; }
	void setDir(const Direction& dir) { m_dir = (Direction)dir; }

	//C'tor
	Creature(int row, int col, Direction dir, Board& b);
	virtual bool move(Mode mode) = 0;

	Creature& operator=(const Creature& right) {

		setRow(right.getRow());
		setCol(right.getCol());
		setDir(right.getDir());
		// No reference for board, points and lives etc.. cause we use (=) only in children

		return *this;
	}

	void encounterWallOrTunnel(Mode mode);
};