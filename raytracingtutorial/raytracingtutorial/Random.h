#pragma once

#include <stdlib.h> 

float GetRand0To1()
{
	return float(rand()) / float(RAND_MAX + 1);
}