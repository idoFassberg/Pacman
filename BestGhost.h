#pragma once
#include "Ghost.h"

class BestGhost : public Ghost{

public:

	BestGhost(Board& b) : Ghost(b) {}
	void changeDirectionByLevel(Direction NotToGoDir);
};