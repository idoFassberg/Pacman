#include "Ghost.h"

bool Ghost::move(Mode mode) {

	m_moves++;

	if (m_moves % 2 != 0)
		return false;

	bool isEncounterPacman = false;
	bool isEncounterFruit = false;
	
	if (mode == SILENT || mode == LOAD)
	{
		int temp;
		m_board.getStepsFile() >> temp;
		setDir((Direction)temp);
	}
	else
	{
		Direction NotToGoDir = FindOppisteDIR(getDir());
		changeDirectionByLevel(NotToGoDir);
		if (mode == SAVE)
			m_board.getStepsFile() << getDir() << " ";
	}

	int nextRow = getRow();
	int nextCol = getCol();
	Direction nextDir = getDir();
	char nextChUnder = getChUnder();

	switch (getDir()) {

	case UP:
		nextRow = getRow() - 1;
		break;

	case DOWN:
		nextRow = getRow() + 1;
		break;

	case LEFT:
		nextCol = getCol() - 1;
		break;

	case RIGHT:
		nextCol = getCol() + 1;
		break;
	}

	switch (m_board.getCharOnBoard(nextRow, nextCol)) {

	case WALL: case TUNNEL: // Wall or Tunnel
		encounterWallOrTunnel(mode);
		break;

	case '@':
		encounterGhost();
		isEncounterPacman = true;
		m_board.setCharOnBoard(' ', nextRow, nextCol);

		if (mode != SILENT) {
			gotoxy(nextRow, nextCol);
			cout << ' ';
		}
		break;

	case BREADCRUMB: //food

		m_board.setCharOnBoard(m_chUnder, getRow(), getCol());

		if (mode != SILENT) {
			gotoxy(getRow(), getCol());
			if (m_board.getGameColor())
				setTextColor(BREADCRUMB_COLOR);
			cout << m_chUnder;
		}

		nextChUnder = m_board.getCharOnBoard(nextRow, nextCol);

		setRow(nextRow);
		setCol(nextCol);
		setDir(nextDir);
		setChUnder(nextChUnder);

		m_board.setCharOnBoard('$', getRow(), getCol());

		if (mode != SILENT) {
			gotoxy(getRow(), getCol());
			if (m_board.getGameColor())
				setTextColor(GHOST_COLOR);
			cout << '$';
		}
		break;

	case ' ': //nothing

		m_board.setCharOnBoard(m_chUnder, getRow(), getCol());

		if (mode != SILENT) {
			gotoxy(getRow(), getCol());
			if (m_board.getGameColor())
				setTextColor(BREADCRUMB_COLOR);
			cout << m_chUnder;
		}
		nextChUnder = m_board.getCharOnBoard(nextRow, nextCol);

		setRow(nextRow);
		setCol(nextCol);
		setDir(nextDir);
		setChUnder(nextChUnder);
		m_board.setCharOnBoard('$', getRow(), getCol());

		if (mode != SILENT) {
			gotoxy(getRow(), getCol());
			if (m_board.getGameColor())
				setTextColor(GHOST_COLOR);
			cout << '$';
		}
		break;

	case '$':
		if (mode == SAVE || mode == REGULAR)
		{
			setDir((Direction)(rand() % 4));
			if (mode == SAVE)
				m_board.getStepsFile() << getDir() << " ";
		}
		else// LOAD OR SILENT
		{
			int temp;
			m_board.getStepsFile() >> temp;
			setDir((Direction)temp);
		}
		break;

	case '5': case '6': case '7': case '8': case '9': // ghost encounter fruit

		isEncounterFruit = true;
		m_board.setCharOnBoard(m_chUnder, getRow(), getCol());

		if (mode != SILENT) {
			gotoxy(getRow(), getCol());
			if (m_board.getGameColor())
				setTextColor(BREADCRUMB_COLOR);
			cout << m_chUnder;
		}
		m_chUnder = m_board.getCharUnderFruit();

		setRow(nextRow);
		setCol(nextCol);
		setDir(nextDir);

		m_board.setCharOnBoard('$', getRow(), getCol());

		if (mode != SILENT) {
			gotoxy(getRow(), getCol());
			if (m_board.getGameColor())
				setTextColor(GHOST_COLOR);
			cout << '$';
		}
	}
	return (isEncounterPacman || isEncounterFruit);
}

void Ghost::reset(int index,Mode mode) {

	m_board.setCharOnBoard(m_chUnder, getRow(), getCol());

	if (mode != SILENT) {
		gotoxy(getRow(), getCol());
		if (m_board.getGameColor())
			setTextColor(BREADCRUMB_COLOR);
		cout << m_chUnder;
	}
	initGhost(index,mode);
}

void Ghost::initGhost(int index,Mode mode) {

	setRow(m_board.getGhostsPos()[index].getRow());
	setCol(m_board.getGhostsPos()[index].getCol());
	if (mode == SAVE || mode == REGULAR)
	{
		setDir((Direction)LEFT);
		if (mode == SAVE)
			m_board.getStepsFile() << getDir() << " ";
	}
	else// LOAD OR SILENT
	{
		int temp;
		m_board.getStepsFile() >> temp;
		setDir((Direction)temp);

	}
	m_chUnder = ' ';

	if (mode == SILENT)
		return;
	gotoxy(getRow(), getCol());
	if (m_board.getGameColor())
		setTextColor(GHOST_COLOR);
	cout << '$';
}

void Ghost::encounterGhost() {

	//replace last pacman's pos to ' '.
	m_board.setCharOnBoard(m_chUnder, getRow(), getCol());

	if (m_board.getMode() != SILENT) {
		gotoxy(getRow(), getCol());
		if (m_board.getGameColor())
			setTextColor(BREADCRUMB_COLOR);
		cout << m_chUnder;
	}
}

Ghost::Ghost(Board& b) : Creature(1, 1, RIGHT, b), m_chUnder(BREADCRUMB) {}

Direction Ghost::FindOppisteDIR(Direction dir)
{
	Direction resDir;

	switch (dir)
	{
	case UP:
		resDir = DOWN;
		break;
	case DOWN:
		resDir = UP;
		break;
	case RIGHT:
		resDir = LEFT;
		break;
	case LEFT:
		resDir = RIGHT;
		break;
	}
	return resDir;
}