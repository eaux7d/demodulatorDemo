#include "DemodulateLibMath.h"
#include <cmath>
#include "Tasks.hpp"

void DemodulateAm(std::vector <float> & output, std::vector<IQElement> & source)
{
	if (output.size() < source.size())
	{
		throw std::runtime_error("The output vector has wrong length!");
	}

	for (size_t i = 0; i != source.size(); ++i)
	{
		output[i] = source[i].Magnitude();
	}
}

void DemodulateFm(std::vector <float> & output, std::vector<IQElement> & source)
{
	if (output.size() < source.size() - 1)
	{
		throw std::runtime_error("The output vector has wrong length!");
	}

	std::cout << "ins:\n";
	for (size_t i = 0; i != source.size() - 1; ++i)
	{
		output[i] = RotateElement(source[i + 1], source[i].GetConjugated()).getPhase();
		//std::cout << source[i + 1];
		//std::cout << RotateElement(source[i + 1], source[i].GetConjugated());
	}
	std::cout << "out\n";
}

IQElement RotateElement(const IQElement & a, const IQElement & b)
{
	std::cout << a.I * b.I - a.Q * b.Q << "\n";
	std::cout << a.I * b.I + a.Q * b.Q << "\n";
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

