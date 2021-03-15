#include <iostream>
#include <fstream>
#include "demolib/DemodulateLibTypes.h" 
#include "demolib/DemodulateLibMath.h" 
#include "demolib/fir_sr1M_cut_50k_x2=150k.h"
#include "demolib/Tasks.hpp"

void ProceedIQInput( std::vector<IQElement> & input, std::fstream & fout, char mode)
{
	std::vector<float> output;
	output.resize(input.size());

	bool doOutput = true;
	//algo
	if (!input.empty())
	{
		switch (mode)
		{
		case ('a'):
		{

			DemodulateAm(output, input);

			break;
		}

		case ('f'):
		{
			ApplyFilter(input, &fir_sr1M_cut50k_x2_150k::B[0], fir_sr1M_cut50k_x2_150k::size);
			DemodulateFm(output, input);

			break;
		}

		//for output
		case ('o'):
		{
			std::cout << "No algo choosen, only output from binary format! \n";

			break;
		}

		case ('d'):
		default:
		{
			std::cerr << "No algo choosen!\n";
			doOutput = false;
			break;
		}
		}
	}


	{
		if (doOutput)
		{
			for (int i = 0; i != input.size(); ++i)
				fout << output[i] << "\n";
		}

	}
}

void ProceedFlInput(const std::vector<float> & input, std::fstream & fout, char mode,float param)
{
	//outputs
	int c = 0;
	std::vector<float> flout;
	std::vector<IQElement> iqout;
	std::vector<size_t> stout;

	switch (mode)
	{

		//d - diff function
		case ('d'):
		{
			Tasks::diff<float>(input, flout);
			break;
		}

		//r - rectpulse
		case ('r'):
		{
			Tasks::rectpulse(input, flout, (int)param);
			break;
		}

		//c - count more than
		case ('c'):
		{
			Tasks::count_more_than(input, param);
			break;
		}

		//p - psk_mod
		case ('p'):
		{
			std::vector<int> t_in;
			t_in.resize(input.size());

			for (size_t i = 0; i != input.size(); ++i)
				t_in[i] = (int)input[i];

			Tasks::psk_mod(t_in, iqout, (int)param);
			break;
		}

		//f - find_local_peaks.
		case ('f'):
		{
			Tasks::FindLocalPeaks(input, stout, 6, param);
			break;
		}

		//output to out 
		default:
		{
			for (size_t i = 0; i != input.size(); ++i)
				flout[i] = input[i];
		}
	}

	//output
	if (c)
	{
		std::cout << c << "\n";
	}
	else if (!flout.empty())
	{
		for (size_t i = 0; i != input.size(); ++i)
			fout << flout[i] << "\n";
	}
	else if (!iqout.empty())
	{
		for (size_t i = 0; i != input.size(); ++i)
			fout << iqout[i];
	}
	else if (!stout.empty())
	{
		for (size_t i = 0; i != input.size(); ++i)
			fout << stout[i] << "\n";
	}

}