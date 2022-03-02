#pragma once
#include "Error.h"

class LongerLineThanFirstOne : public Error {

public:
	LongerLineThanFirstOne() : Error("Longer Line Than First One") {}
};