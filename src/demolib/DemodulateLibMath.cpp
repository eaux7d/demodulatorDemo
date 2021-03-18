#include "DemodulateLibMath.h"
#include <cmath>
#include "Tasks.hpp"

void DemodulateAm(std::vector <float> & output, std::vector<IQElement> & source)
{

	for (size_t i = 0; i != source.size(); ++i)
	{
		output[i] = source[i].Magnitude();
	}
}

void DemodulateFm(std::vector <float> & output, std::vector<IQElement> & source)
{
	for (size_t i = 0; i != source.size() - 1; ++i)
	{
		output[i] = RotateElement(source[i + 1], source[i].GetConjugated()).getPhase();
	}
}

IQElement RotateElement(const IQElement & a, const IQElement & b)
{
	return IQElement(a.I * b.I - a.Q * b.Q, a.Q * b.I + a.I * b.Q);
}

void ApplyFilter(std::vector<IQElement> & src, const float * filter, const int & size)
{
	if (!filter)
		return;

	for (int i = size; i != src.size(); ++i)
	{

		IQElement e(0.f, 0.f);

		for (int j = 0; j != size; ++j)
		{
			e += src[i - j] * filter[j];
		}

		src[i] = e;
	}
}

