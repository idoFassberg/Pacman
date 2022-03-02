#pragma once
#include "Ghost.h"

class NoviceGhost : public Ghost{


public:

	NoviceGhost(Board& b) : Ghost(b) {}
	void changeDirectionByLevel(Direction NotToGoDir){}
	
};