#include "pacman.h"

bool Pacman::move(Mode mode) {
	
	Pacman nextPac = *this;
	bool isEncounteredGhost = false;
	bool isEncounteredFruit = false;

	switch (getDir()) {

	case UP:
		nextPac.setRow(getRow() - 1);
		break;

	case DOWN:
		nextPac.setRow(getRow() + 1);
		break;

	case LEFT:
		nextPac.setCol(getCol() - 1);
		break;

	case RIGHT:
		nextPac.setCol(getCol() + 1);
		break;
	}

	switch (m_board.getCharOnBoard(nextPac.getRow(), nextPac.getCol())) {

	case WALL: //wall		
		break;

	case TUNNEL: //tunnel
		enterTunnel();
		break;

	case '$': //ghost
		encounterGhost();
		isEncounteredGhost = true;
		break;

	case BREADCRUMB://food
		m_board.setRemainFood();
		nextPac.setPoints(1);
		m_board.setCharOnBoard('@', nextPac.getRow(), nextPac.getCol());

		if (m_board.getMode() != SILENT) {
			gotoxy(nextPac.getRow(), nextPac.getCol());
			if (m_board.getGameColor())
				setTextColor(PACMAN_COLOR);
			cout << '@';
		}

		m_board.setCharOnBoard(' ', getRow(), getCol());

		if (m_board.getMode() != SILENT) {
			gotoxy(getRow(), getCol());
			cout << ' ';
		}
		*this = nextPac;
		break;

	case ' ': //empty space
		m_board.setCharOnBoard('@', nextPac.getRow(), nextPac.getCol());

		if (m_board.getMode() != SILENT) {
			gotoxy(nextPac.getRow(), nextPac.getCol());
			if (m_board.getGameColor())
				setTextColor(PACMAN_COLOR);
			cout << '@';
		}

		m_board.setCharOnBoard(' ', getRow(), getCol());

		if (m_board.getMode() != SILENT) {
			gotoxy(getRow(), getCol());
			cout << ' ';
		}
		*this = nextPac;
		break;

	case '5': case '6': case '7': case '8': case '9': // fruit
		isEncounteredFruit = true;
		if (m_board.getCharUnderFruit() == BREADCRUMB)
		{
			m_board.setRemainFood();
			nextPac.setPoints(1);
		}

		m_board.setCharOnBoard(' ', getRow(), getCol());
		if (m_board.getMode() != SILENT) {
			gotoxy(getRow(), getCol());
			cout << ' ';
		}
		*this = nextPac;

		m_board.setCharOnBoard('@', getRow(), getCol());

		if (m_board.getMode() != SILENT) {
			gotoxy(getRow(), getCol());
			if (m_board.getGameColor())
				setTextColor(PACMAN_COLOR);
			cout << '@';
		}
	}

	m_board.setPacmanPos(getRow(), getCol()); // update the pacman position on the board class

	return (isEncounteredGhost || isEncounteredFruit);
}

void Pacman::enterTunnel() {

	m_board.setCharOnBoard(' ', getRow(), getCol());

	if (m_board.getMode() != SILENT) {
		gotoxy(getRow(), getCol());
		cout << ' ';
	}

	switch (getDir()) { // this->getDir()

	case UP: // upper tunnel -> goes to down tunnel
		setRow(m_board.getBoardSize().getRow() - 2);
		break;

	case DOWN: // down tunnel -> goes to upper tunnel
		setRow(1);
		break;

	case LEFT: // left tunnel -> goes to right tunnel
		setCol(m_board.getBoardSize().getCol() - 2);
		break;

	case RIGHT: // right tunnel -> goes to left tunnel
		setCol(1);
		break;
	}

	switch (m_board.getCharOnBoard(getRow(), getCol())) { //pos after exit the tunnel

	case ' ':
		m_board.setCharOnBoard('@', getRow(), getCol());

		if (m_board.getMode() != SILENT) {
			gotoxy(getRow(), getCol());
			if (m_board.getGameColor())
				setTextColor(PACMAN_COLOR);
			cout << '@';
		}
		break;

	case BREADCRUMB:
		m_points++;
		m_board.setRemainFood();
		m_board.setCharOnBoard('@', getRow(), getCol());

		if (m_board.getMode() != SILENT) {
			gotoxy(getRow(), getCol());
			if (m_board.getGameColor())
				setTextColor(PACMAN_COLOR);
			cout << '@';
		}
		break;

	case '$':
		encounterGhost();
		break;

	}
}

void Pacman::encounterGhost() {

	m_remainLife--;
	printPointsAndRemainLife();

	//replace last pacman's pos to ' '.
	m_board.setCharOnBoard(' ', getRow(), getCol());

	if (m_board.getMode() != SILENT) {
		gotoxy(getRow(), getCol());
		cout << ' ';
	}

	setRow(m_board.getPacmanFirstPos().getRow());
	setCol(m_board.getPacmanFirstPos().getCol());

	m_board.setCharOnBoard('@', getRow(), getCol());

	if (m_board.getMode() != SILENT) {
		gotoxy(getRow(), getCol());
		if (m_board.getGameColor())
			setTextColor(PACMAN_COLOR);
		cout << '@';
	}
}

void Pacman::printPointsAndRemainLife() {

	setTextColor(WHITE);

	if (m_board.getMode() != SILENT) {
		gotoxy(m_board.getAmpPos().getRow() + 1, m_board.getAmpPos().getCol() + 3);
		cout << "Points:" << m_points;
		cout << " Life:" << m_remainLife << endl << endl;
	}
	gotoxy(0, 0);
}

bool Pacman::isLose() {

	if (m_remainLife == 0)
		return true;
	return false;
}

Pacman::Pacman(Board& b) : Creature(1, 1, RIGHT, b), m_points(0), m_remainLife(3) {}

void Pacman::init(Mode mode) {

	setRow(m_board.getPacmanFirstPos().getRow());
	setCol(m_board.getPacmanFirstPos().getCol());

	if (mode == SILENT)
		return;
	gotoxy(getRow(), getCol());
	if (m_board.getGameColor())
		setTextColor(PACMAN_COLOR);
	cout << '@';
}