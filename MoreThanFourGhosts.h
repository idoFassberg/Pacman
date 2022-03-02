#pragma once
#include "Error.h"

class MoreThanFourGhosts : public Error {

public:
	MoreThanFourGhosts() : Error("More Than Four Ghosts") {}
};