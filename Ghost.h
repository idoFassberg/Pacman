#pragma once
#include "Creature.h"

class Ghost : public Creature {

private:

	char m_chUnder = BREADCRUMB;

protected:

	int m_moves = 0;

public:

	Ghost(Board& b);
	void reset(int index,Mode mode);
	void initGhost(int index,Mode mode);
	bool move(Mode mode);
	void encounterGhost();
	virtual void changeDirectionByLevel(Direction NotToGoDir) = 0;
	char getChUnder() const { return m_chUnder; }
	void setChUnder(char ch) { m_chUnder = ch; }
	Direction FindOppisteDIR(Direction dir);
};
