#pragma once
#include "Error.h"

class MoreThanOnePacman : public Error {

public:
	MoreThanOnePacman() : Error("More Than One Pacman") {}
};