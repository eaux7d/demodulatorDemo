#include <fstream>
#include <iostream>
#include <string>
#include "demolib/DemodulateLibTypes.h" 
#include "demolib/DemodulateLibMath.h" 
#include "demolib/fir_sr1M_cut_50k_x2=150k.h"
#include "exe/ProceedInput.h"
#include "demolib/Tasks.hpp"

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

	//outputs
	int c = 0;
	std::vector<float> flout;
	std::vector<IQElement> iqout;
	std::vector<size_t> stout;

	switch (mode)
	{
		case ('i'):
			{
				auto input = InputFromFile<IQElement>(fin1);
				
				break;
			}

		case ('f'):
		{
			auto input = InputFromFile<float>(fin1);

			Tasks::diff(input, flout);

			break;
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
