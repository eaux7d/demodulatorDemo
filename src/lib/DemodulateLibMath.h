#pragma once
#include "DemodulateLibTypes.h"


void demodulateAm(float * output, vecIQ const & source)
{
	for (int i = 0; i != source.size(); ++i)
	{
		output[i] = sqrt(source[i].I * source[i].I + source[i].Q * source[i].Q);
	}
}