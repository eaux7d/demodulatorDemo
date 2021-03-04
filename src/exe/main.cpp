#include <fstream>
#include <iostream>
#include <string>
#include "../lib/DemodulateLibTypes.h" 
#include "../lib/DemodulateLibMath.h" 

int main(int argc, char * argv[])
{

	std::string filePath;
	char mode = 'd';
	int freq = 24000;

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
		}
	}

	std::fstream fin("data\\am.flt",std::fstream::binary|std::fstream::in);
	//std::ofstream fout("E:/stc/1-AM/out.txt");

	if (!fin)
	{
		std::cerr << "Can't open file!";
		return 1;
	}

	float r = 0.f, i = 0.f;

	while (!fin.eof())
	{
		fin.read((char *)&r, sizeof(float));
		fin.read((char *)&i, sizeof(float));

		//fout << r << " " << i << "\n";
	}

	return 0;
}