#pragma once
#include <vector>

struct IQSignal
{
	float I;
	float Q;
};

typedef std::vector<IQSignal> vecIQ;