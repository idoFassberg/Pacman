#include "BestGhost.h"

void BestGhost::changeDirectionByLevel(Direction NotToGoDir) {

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
		if (dirCol != NotToGoDir)
			setDir(dirCol);
		else
			setDir(dirRow);
	}
	else if (NextDirCol && dirCol != NotToGoDir)
		setDir(dirCol);

	else if (NextDirRow && dirRow != NotToGoDir)
		setDir(dirRow);

	else {


		for (int i = 0; i < 4; i++)
		{
			if (i != int(dirCol) && i != int(dirRow) && i != int(NotToGoDir))
				tmp = i;
		}
		setDir((Direction)tmp);
	}
}