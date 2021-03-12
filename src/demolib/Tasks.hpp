#include "DemodulateLibTypes.h"
#include <iostream>
#include <vector>
#include <cmath>

template <typename T>
void Diff(const std::vector<T> & src, std::vector<T> & out)
{
	if (src.size() < 2)
	{
		std::cerr << "The source vector's size is lower 2! Need at least 2 element for diff operation!\n";
		return 0;
	}

	if (out.size() < src.size())
	{
		out.resize(src.size());
	}

	for (size_t i = 0; i != src.size() - 1; ++i)
		out[i] = src[i + 1] - src[i];

}

template <typename T>
void Rectpulse(const std::vector<T> & src, std::vector<T> & out, size_t n)
{
	if (src.empty())
	{
		std::cerr << "The source vector is empty!\n";
		return;
	}

	out.resize(src.size() * n);

	for (size_t i = 0; i != src.size(); ++i)
	{
		for (size_t j = 0; j != n; ++j)
		{
			out[i * n + j] = src[i];
		}
	}

}

template <typename T>
int CountMoreThan(const std::vector<T> & src, const T & val)
{
	int c = 0;

	for (size_t i = 0; i != src.size(); ++i)
		if (src[i] > val) ++c;

	return c;

}

void PhaseMod(const Ivec & src, IQvec & out, size_t M)
{
	int c = M;

	//checks
	{
		while (c != 1)
		{
			if (c % 2 != 0)
			{
				std::cerr << "M should be represented as 2^N! \n";
				return;
			}
		}

		for (size_t i = 0; i != src.size(); ++i)
		{
			if (src[i] < 0 || src[i] > (int)(M - 1))
			{
				std::cerr << "Input vector should consist of values < M! \n";
				return;
			}
		}
	}

	if (out.size() < src.size())
		out.resize(src.size());

	for (size_t i = 0; i != src.size(); ++i)
	{
		float angle = src[i] * PI * 2.0f / M;
		out[i] = IQElement(cosf(angle), sinf(angle));
	}

}

void FindLocalPeaks(const Flvec & src, STvec & idx_out, size_t win, float level)
{
	if (src.size() < 2 * win)
	{
		std::cerr << "The source signal is too short! \n";
		return;
	}

	bool isInLocalMaxZone = false;
	float maxVal = 0.f;
	size_t maxValIdx = 0;

	for (size_t i = win; i != src.size() - win; ++i)
	{

		if (!isInLocalMaxZone)
		{
			//are we getting into local max zone?
			if ((src[i] - src[i - win] > level) && (src[i] - src[i + win] > level))
			{
				isInLocalMaxZone = true;

				maxVal = src[i];
				maxValIdx = i;

				idx_out.push_back(maxValIdx);
			}

		}
		else
		{
			//ok, maybe we are out of zone now?
			if (src[i] - src[i - win] < 0.0f)
			{
				//if so, set the last element max idx we found
				isInLocalMaxZone = false;
				idx_out.back() = maxValIdx;
			}

		}

		if (isInLocalMaxZone)
		{
			//if we are in it, let's get max!
			if (src[i] > maxVal)
			{
				maxVal = src[i];
				maxValIdx = i;
			}
		}

	}

	//if we didn't get out of local max zone should set max at last!
	if (isInLocalMaxZone)
		idx_out.back() = maxValIdx;

}

