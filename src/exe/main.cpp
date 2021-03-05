#include <fstream>
#include <iostream>
#include <string>
#include "lib/DemodulateLibTypes.h" 
#include "lib/DemodulateLibMath.h" 

int main(int argc, char * argv[])
{
	//Input
	std::string filePath;
	std::string outputFile;
	char mode = 'd';
	int freq = 24000;

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
					mode = argv[i + 1][0];

				//freq (rate)
				if (argv[i][1] == 'r')
					freq = std::stoi(std::string(argv[i + 1]));

				//outputFile
				if (argv[i][1] == 'o')
					outputFile = std::string(argv[i + 1]);
			}
		}
	}

	std::fstream fin(filePath, std::fstream::binary | std::fstream::in);

	//checks
	{
		if (filePath.empty())
		{
			std::cerr << "The input file is not specified! Shutting down!\n";
			return 1;
		}

		if (!fin)
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

	IQvec input;

	//input
	{
		int size = 0;

		fin.seekg(0, std::ifstream::end);
		size = fin.tellg() / (sizeof(IQElement));
		input.resize(size);
		fin.seekg(0, std::ifstream::beg);

		fin.read((char *)&input[0], sizeof(IQElement) * size);
	}

	Flvec output;
	output.resize(input.size());

	bool doOutput = true;
	//algo
	{
		switch (mode)
		{
			case ('a'):
			{

				demodulateAm(output, input);

				break;
			}

			case ('f'):
			{
				demodulateFm(output, input);

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

		fout.close();
	}

	return 0;
}