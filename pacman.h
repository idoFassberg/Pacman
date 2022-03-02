#pragma once
#include "Creature.h"

class Pacman : public Creature {

private:

	int m_points;
	int m_remainLife;

public:
	// getters
	int getRemainLife()const { return m_remainLife; }
	int getPoints() const { return m_points; }
	// setters
	void setPoints(int points) { m_points += points; }
	void setRemainLife() { m_remainLife--; }
	void initRemainLife() { m_remainLife = 3; }

	bool move(Mode mode);
	void enterTunnel();
	void encounterGhost();
	void printPointsAndRemainLife();
	bool isLose();

	Pacman(Board& b);
	void init(Mode mode);
};