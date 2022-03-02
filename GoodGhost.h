#pragma once
#include "Ghost.h"

class GoodGhost : public Ghost{


public:

	GoodGhost(Board& b) : Ghost(b) {}
	void changeDirectionByLevel(Direction NotToGoDir);
};