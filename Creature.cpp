#include "Creature.h"

Creature::Creature(int row, int col, Direction dir, Board& b) : m_row(row), m_col(col), m_dir(dir), m_board(b) {}

void Creature::encounterWallOrTunnel(Mode mode) {

   switch (mode){

	case REGULAR: case SAVE:

	Direction tmp;

		do {
			tmp = (Direction)(rand() % 4);
		} while (tmp == getDir());
		setDir(tmp);

		if(mode==SAVE)
		 m_board.getStepsFile() << getDir() << " ";
		break;

	case LOAD: case SILENT:

		int temp;
		m_board.getStepsFile() >> temp;
		setDir(Direction(temp));
		break;
   }
}