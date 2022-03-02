#pragma once
#include "Creature.h"

class Fruit : public Creature {

private:

	char m_chUnder = BREADCRUMB;
	char m_score;
	bool m_isOnBoard = true;
	int m_moves_on_board = 1;
	int m_moves_not_on_board = 1;

public:

	Fruit(Board& b);

	bool getIsOnBoard(){ return m_isOnBoard; }
	int getMovesOnBoard() { return m_moves_on_board;}
	int getMovesNotOnBoard() { return m_moves_not_on_board; }
	bool move(Mode mode);
	void encounterPacman();
	void init(Mode mode);
	char getScore() { return m_score; }
	void setIsOnBoardFalse() { m_isOnBoard = false; }
};