#include <fstream>
#include <iostream>
#include <string>
#include "demolib/DemodulateLibTypes.h" 
#include "demolib/DemodulateLibMath.h" 
#include "demolib/fir_sr1M_cut_50k_x2=150k.h"
#include "exe/ProceedInput.h"
#include "demolib/Tasks.hpp"
#include "demolib/WaveFormat.h"

void TestFindLocalPeaks()
{
	std::vector<float> in_vec;
	std::vector<size_t> idx;

	in_vec.resize(10000);

	for (size_t i = 0; i != in_vec.size(); ++i)
		in_vec[i] = 2.0f * sinf(2 * PI_f * i / 2500.0f) + 0.4f * cosf(2 * PI_f * i / 500.0f);

	Tasks::FindLocalPeaks(in_vec, idx, 250, 0.2f);

	for (size_t i = 0; i != idx.size(); ++i)
		std::cout << idx[i] << "\n";

}

int main(int argc, char * argv[])
{
	//Input
	std::string filePath;
	std::string outputFile;
	char mode = 'd';

	//args
	{
		if (argc > 2)
		{
			for (int i = 1; i != argc - 1; ++i)
			{
				//filepath
				if (argv[i][1] == 'f')
					filePath = std::string(argv[i + 1]);

				//mode
				if (argv[i][1] == 'm')
				{
					if (!(argv[i + 1][0]))
					{
						mode = 'd';
						break;
					}

					//f - float, i - iq signal
					mode = argv[i + 1][0];
				}

				//outputFile
				if (argv[i][1] == 'o')
					outputFile = std::string(argv[i + 1]);

			}
		}
	}

	std::fstream fin1(filePath, std::fstream::binary | std::fstream::in);
	//checks
	{
		if (filePath.empty())
		{
			std::cerr << "The input file is not specified! Shutting down!\n";
			return 1;
		}

		if (!fin1)
		{
			std::cerr << "Can't open input file! Shutting down!\n";
			return 1;
		}

		if (outputFile.empty())
		{
			std::cerr << "The output dir is not specified! Will use out.txt near exe!\n";
			outputFile = "out.txt";
		}
	}

	std::fstream fout(outputFile,std::fstream::out);
	std::fstream fout2("input.txt", std::fstream::out);

	fout.precision(12);

	//outputs
	int c = 0;
	std::vector<float> flout;
	std::vector<float> iout;
	std::vector<IQElement> iqout;
	std::vector<size_t> stout;

	switch (mode)
	{
		case ('q'):
			{
				auto input = InputFromFile<IQElement>(fin1);
				
				//Tasks::rectpulse(input, iqout, 4);
				iqout.resize(input.size());
				for (size_t i = 0; i != input.size(); ++i)
					iqout[i] = input[i];

				break;
			}

		case ('f'):
		{
			auto input = InputFromFile<float>(fin1);

			//Tasks::diff(input, flout);
			//c = Tasks::count_more_than(input, 115.2695f);
			//Tasks::FindLocalPeaks(input, stout, 640, 6.0f);

			//for (size_t i = 0; i != input.size(); ++i)
				//fout2 << input[i] << "\n";

			break;
		}

		case ('i'):
		{
			auto input = InputFromFile<int>(fin1);

			//Tasks::psk_mod(input, iqout, 8);
			iout.resize(input.size());
			for (size_t i = 0; i != input.size(); ++i)
				iout[i] = input[i];

			break;
		}

		case ('t'):
		{
			TestFindLocalPeaks();
			break;
		}

		case ('a'):
		{
			WaveFile wav1;
			wav1.ReadWav(filePath);
			wav1.ReadFileInfo();
			//wav1.GetWaveData();
			//auto vec = wav1.GetWaveData<std::vector<std::pair<int8_t, int8_t>>>();
		}

	}


	//output
	if (c)
	{
		std::cout << c << "\n";
	}
	else if (!flout.empty())
	{
		for (size_t i = 0; i != flout.size(); ++i)
			fout << flout[i] << "\n";
	}
	else if (!iout.empty())
	{
		for (size_t i = 0; i != iout.size(); ++i)
			fout << iout[i] << "\n";
	}
	else if (!iqout.empty())
	{
		for (size_t i = 0; i != iqout.size(); ++i)
			fout << iqout[i];
	}
	else if (!stout.empty())
	{
		for (size_t i = 0; i != stout.size(); ++i)
			fout << stout[i] << "\n";
	}



	return 0;
}
