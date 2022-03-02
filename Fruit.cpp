#include "Fruit.h"

Fruit::Fruit(Board& b) : Creature(8, 10, RIGHT, b), m_score('5'), m_isOnBoard(true) {}

bool Fruit::move(Mode mode) {

	if (m_isOnBoard) {
		if (m_moves_on_board % 4 != 0) { // for moving slower than ghost
			m_moves_on_board++;
			return false;
		}

		if (m_moves_on_board % 120 == 0) {
			m_isOnBoard = false;
			m_board.setCharOnBoard(m_chUnder, getRow(), getCol());

			if (m_board.getMode() != SILENT) {
				gotoxy(getRow(), getCol());
				if (m_board.getGameColor())
					setTextColor(BREADCRUMB_COLOR);
				cout << m_chUnder;
			}
			m_moves_on_board++;
			return false;
		}
		m_moves_on_board++;
	}

	else {
		m_moves_not_on_board++;
		m_moves_on_board = 1;
		if (m_moves_not_on_board % 50 == 0) {
			m_isOnBoard = true;
			init(mode);
		}
		else
			return false;
	}


	Fruit nextFruitMove = *this;
	bool isEncounteredPacman = false;

	switch (getDir()) {

	case UP:
		nextFruitMove.setRow(getRow() - 1);
		break;

	case DOWN:
		nextFruitMove.setRow(getRow() + 1);
		break;

	case LEFT:
		nextFruitMove.setCol(getCol() - 1);
		break;

	case RIGHT:
		nextFruitMove.setCol(getCol() + 1);
		break;
	}

	switch (m_board.getCharOnBoard(nextFruitMove.getRow(), nextFruitMove.getCol())) {

	case WALL: case TUNNEL: // Wall or Tunnel
		encounterWallOrTunnel(mode);
		break;

	case '@':
		encounterPacman();
		isEncounteredPacman = true;
		break;

	case BREADCRUMB: // Food
		m_board.setCharOnBoard(m_chUnder, getRow(), getCol());

		if (m_board.getMode() != SILENT) {
			gotoxy(getRow(), getCol());
			if (m_board.getGameColor())
				setTextColor(BREADCRUMB_COLOR);
			cout << m_chUnder;
		}
		nextFruitMove.m_chUnder = m_board.getCharOnBoard(nextFruitMove.getRow(), nextFruitMove.getCol());
		m_board.setCharUnderFruit(nextFruitMove.m_chUnder);
		*this = nextFruitMove;
		m_board.setCharOnBoard(m_score, getRow(), getCol());

		if (m_board.getMode() != SILENT) {
			gotoxy(getRow(), getCol());
			if (m_board.getGameColor())
				setTextColor(FRUIT_COLOR);
			cout << m_score;
		}
		break;

	case ' ': //nothing
		m_board.setCharOnBoard(m_chUnder, getRow(), getCol());

		if (m_board.getMode() != SILENT) {
			gotoxy(getRow(), getCol());
			if (m_board.getGameColor())
				setTextColor(BREADCRUMB_COLOR);
			cout << m_chUnder;
		}
		nextFruitMove.m_chUnder = m_board.getCharOnBoard(nextFruitMove.getRow(), nextFruitMove.getCol());
		m_board.setCharUnderFruit(nextFruitMove.m_chUnder);
		*this = nextFruitMove;
		m_board.setCharOnBoard(m_score, getRow(), getCol());

		if (m_board.getMode() != SILENT) {
			gotoxy(getRow(), getCol());
			if (m_board.getGameColor())
				setTextColor(FRUIT_COLOR);
			cout << m_score;
		}
		break;

	case '$':
		m_isOnBoard = false;
		m_board.setCharOnBoard(m_chUnder, getRow(), getCol());

		if (m_board.getMode() != SILENT) {
			gotoxy(getRow(), getCol());
			if (m_board.getGameColor())
				setTextColor(BREADCRUMB_COLOR);
			cout << m_chUnder;
		}
		break;

	default:
		encounterWallOrTunnel(mode);
	}
	return isEncounteredPacman;
}

void Fruit::encounterPacman() {
	//add fruit score outside this func
	m_isOnBoard = false;
	m_board.setCharOnBoard(m_chUnder, getRow(), getCol());

	if (m_board.getMode() != SILENT) {
		gotoxy(getRow(), getCol());
		if (m_board.getGameColor())
			setTextColor(BREADCRUMB_COLOR);
		cout << m_chUnder;
	}
}

void Fruit::init(Mode mode) {

	m_isOnBoard = true;
	m_moves_not_on_board = 1;
	m_moves_on_board = 1;
	switch (mode) {

	case REGULAR:
		do {
			setRow(rand() % m_board.getBoardSize().getRow());
			setCol(rand() % m_board.getBoardSize().getCol());

		} while (m_board.getCharOnBoard(getRow(), getCol()) != ' ' && m_board.getCharOnBoard(getRow(), getCol()) != BREADCRUMB);
		m_score = ((rand() % 5) + 5) + '0';
		break;

	case LOAD: case SILENT:
		int temp;
		m_board.getStepsFile() >> temp;
		setRow(temp);
		m_board.getStepsFile() >> temp;
		setCol(temp);
		m_board.getStepsFile() >> temp;
		m_score = temp + '0';
		break;

	case SAVE:
		do {
			setRow(rand() % m_board.getBoardSize().getRow());
			setCol(rand() % m_board.getBoardSize().getCol());

		} while (m_board.getCharOnBoard(getRow(), getCol()) != ' ' && m_board.getCharOnBoard(getRow(), getCol()) != BREADCRUMB);
		m_score = ((rand() % 5) + 5) + '0';

		m_board.getStepsFile() << getRow() << " ";
		m_board.getStepsFile() << getCol() << " ";
		m_board.getStepsFile() << m_score - '0' << " ";
		break;
	}

	m_chUnder = m_board.getCharOnBoard(getRow(), getCol());
	m_board.setCharUnderFruit(m_chUnder);
}