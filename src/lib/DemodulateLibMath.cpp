#include "DemodulateLibMath.h"

void demodulateAm(Flvec & output,const  IQvec & source)
{
	for (int i = 0; i != source.size(); ++i)
	{
		output[i] = sqrtf(source[i].I * source[i].I + source[i].Q * source[i].Q);
	}
}

void demodulateFm(Flvec & output,const IQvec & source)
{
	for (int i = 0; i != source.size() - 1; ++i)
	{
		output[i] = RotateElement(source[i + 1], source[i].GetConjugated()).getPhase();
	}
}

IQElement RotateElement(const IQElement & a, const IQElement & b)
{
	return IQElement(a.I * b.I - a.Q * b.Q,a.Q * b.I + a.I * b.Q);
}