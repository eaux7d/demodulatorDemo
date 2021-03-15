#include <fstream>
#include <iostream>
#include <string>
#include "demolib/DemodulateLibTypes.h" 
#include "demolib/DemodulateLibMath.h" 
#include "demolib/fir_sr1M_cut_50k_x2=150k.h"
#include "exe/ProceedInput.h"

int main(int argc, char * argv[])
{
	//Input
	std::string filePath;
	std::string outputFile;
	char mode = 'd';
	char mode2 = 'd';

	float param = 0.0f;
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
					if (!(argv[i + 1][0] && argv[i + 1][1]))
					{
						mode = 'd';
						break;
					}

					//mode - may be i - iqf signal or f - float.  
					mode = argv[i + 1][0];

					//mode2 - the type of conversion. differs for iqf and f signals.
					//i (iqf):
					//a - amplitude demodulation
					//f - freq demodulation
					//o - output to txt with no conversion
					//f:
					//d - diff function
					//r - rectpulse
					//c - count more than
					//p - psk_mod
					//f - find_local_peaks.
					//example: -m ff means we give float signal for input and want the find_local_peaks conversion
					//example2: -m ia means we give iq signal for input and want amplitude demodulation conversion

					mode2 = argv[i + 1][1];

					//float param for input
					//some tasks need params
					//for example -m fc4.5 means that we give as input float with count_more_than proceed and 4.5f as param 
					if (argv[i + 1][2])
					{
						param = std::stof(std::string(&argv[i + 1][2]));
					}
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

	switch (mode)
	{
		case ('i'):
			{
				auto input = InputFromFile<IQElement>(fin1);
				ProceedIQInput(input, fout, mode2);
				break;
			}

		case ('f'):
		{
			auto input = InputFromFile<float>(fin1);
			ProceedFlInput(input, fout, mode2,param);
			break;
		}
	}

	return 0;
}
