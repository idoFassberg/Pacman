#pragma once
#include "Error.h"

class MoreThanOneAmp : public Error {

public:
	MoreThanOneAmp() : Error("More Than One Ampersand") {}
};