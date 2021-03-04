#include "DemodulateLibMath.h"

void demodulateAm(float * output, IQvec const & source)
{
	for (int i = 0; i != source.size(); ++i)
	{
		output[i] = sqrt(source[i].I * source[i].I + source[i].Q * source[i].Q);
	}
}

void demodulateFm(float * output, IQvec const & source)
{
	for (int i = 0; i != source.size(); ++i)
	{
		//output[i] = atan2f(source[i].Q, source[i].I);
	}
}