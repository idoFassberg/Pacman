#include "GoodGhost.h"

void GoodGhost::changeDirectionByLevel(Direction NotToGoDir) {

	if (m_moves % 20 == 0) {
		setDir((Direction)(rand() % 4));
		return;
	}
	if (m_moves % 21 == 0 || m_moves % 22 == 0 || m_moves % 23 == 0 || m_moves % 24 == 0 || m_moves % 25 == 0)
		return;

	Direction dirRow, dirCol;
	bool NextDirRow = false, NextDirCol = false;

	//Row
	if (m_board.getPacmanPos().getRow() == getRow()) { // same row
		dirRow = getDir();
	}
	else if (m_board.getPacmanPos().getRow() > getRow()) { // pacman under ghost
		dirRow = DOWN;
		if (m_board.getCharOnBoard(getRow() + 1, getCol()) != WALL && m_board.getCharOnBoard(getRow() + 1, getCol()) != TUNNEL)
			NextDirRow = true;
	}
	else { // pacman above ghost
		dirRow = UP;
		if (m_board.getCharOnBoard(getRow() - 1, getCol()) != WALL && m_board.getCharOnBoard(getRow() - 1, getCol()) != TUNNEL)
			NextDirRow = true;
	}

	//Col
	if (m_board.getPacmanPos().getCol() == getCol()) { // same col
		dirCol = getDir();
	}
	else if (m_board.getPacmanPos().getCol() > getCol()) { // pacman on right, ghost on left
		dirCol = RIGHT;
		if (m_board.getCharOnBoard(getRow(), getCol() + 1) != WALL && m_board.getCharOnBoard(getRow(), getCol() + 1) != TUNNEL)
			NextDirCol = true;
	}
	else { // pacman on left, ghost on right
		dirCol = LEFT;
		if (m_board.getCharOnBoard(getRow(), getCol() - 1) != WALL && m_board.getCharOnBoard(getRow(), getCol() - 1) != TUNNEL)
			NextDirCol = true;
	}

	int tmp;

	if (NextDirCol && NextDirRow) {

		tmp = (rand() % 2) + 1;

		if (tmp == 1)
			setDir(dirCol);
		else
			setDir(dirRow);
	}
	else if (NextDirCol)
		setDir(dirCol);

	else if (NextDirRow)
		setDir(dirRow);

	else {

		do {
			tmp = rand() % 4;
		} while (tmp == (int)dirCol || tmp == (int)dirRow);

		setDir((Direction)tmp);
	}
}