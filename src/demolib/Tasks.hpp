#pragma once
#include "DemodulateLibTypes.h"
#include <iostream>
#include <vector>
#include <cmath>

//this namespace consists of functions for real projects
namespace Tasks
{
	bool if_baseof_two(size_t M)
	{
		size_t c = M;

		while (c != 1)
		{
			if (c % 2 != 0)
			{
				std::cerr << "M should be represented as 2^N! \n";
				return false;
			}
		}

		return true;
	}

	template <typename T>
	void diff(const std::vector<T> & v_in, std::vector<T> & v_out)
	{
		if (v_in.size() < 2)
		{
			std::cerr << "The source vector's size is lower 2! Need at least 2 element for diff operation!\n";
			return;
		}

		if (v_out.size() < v_in.size())
		{
			v_out.resize(v_in.size());
		}

		for (size_t i = 0; i != v_in.size() - 1; ++i)
			v_out[i] = v_in[i + 1] - v_in[i];

	}

	template <typename T>
	void rectpulse(const std::vector<T> & v_in, std::vector<T> & v_out, size_t n)
	{
		if (v_in.empty())
		{
			std::cerr << "The source vector is empty!\n";
			return;
		}

		v_out.resize(v_in.size() * n);

		for (size_t i = 0; i != v_in.size(); ++i)
		{
			for (size_t j = 0; j != n; ++j)
			{
				v_out[i * n + j] = v_in[i];
			}
		}

	}

	template <typename T>
	int count_more_than(const std::vector<T> & v_in,T val)
	{
		int c = 0;

		for (size_t i = 0; i != v_in.size(); ++i)
			if (v_in[i] > val)
			{
				++c;
			}

		return c;

	}

	void psk_mod(const std::vector<int> & v_in, std::vector<IQF> & v_out, size_t M)
	{
		//checks
		{
			if (!if_baseof_two(M))
			{
				return;
			}

			int c = count_more_than(v_in, (int)M);

			if (c != 0)
			{
				std::cerr << "Input vector should consist of values < M! \n";
				return;
			}

		}

		if (v_out.size() < v_in.size())
			v_out.resize(v_in.size());

		for (size_t i = 0; i != v_in.size(); ++i)
		{
			float angle = v_in[i] * PI_f * 2.0f / (float)M;
			v_out[i] = IQElement(cosf(angle), sinf(angle));
		}

	}

	void FindLocalPeaks(const std::vector<float> & v_in, std::vector<size_t> & idx_peak, size_t len_win, float level)
	{
		if (v_in.size() < 2 * len_win)
		{
			std::cerr << "The source signal is too short! \n";
			return;
		}

		bool isInLocalMaxZone = false;
		float maxVal = 0.f;
		size_t maxValIdx = 0;

		for (size_t i = len_win; i != v_in.size() - len_win; ++i)
		{

			if (!isInLocalMaxZone)
			{
				//are we getting into local max zone?
				if ((v_in[i] - v_in[i - len_win] > level) && (v_in[i] - v_in[i + len_win] > level))
				{
					isInLocalMaxZone = true;

					maxVal = v_in[i];
					maxValIdx = i;

					idx_peak.push_back(maxValIdx);
				}

			}
			else
			{
				//ok, maybe we are out of zone now?
				if (v_in[i] - v_in[i - len_win] < 0.0f)
				{
					//if so, set the last element max idx we found
					isInLocalMaxZone = false;
					idx_peak.back() = maxValIdx;
				}

			}

			if (isInLocalMaxZone)
			{
				//if we are in it, let's get max!
				if (v_in[i] > maxVal)
				{
					maxVal = v_in[i];
					maxValIdx = i;
				}
			}

		}

		//if we didn't get v_out of local max zone should set max at last!
		if (isInLocalMaxZone)
			idx_peak.back() = maxValIdx;

	}

}

