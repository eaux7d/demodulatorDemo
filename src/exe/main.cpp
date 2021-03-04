#include <fstream>
#include <iostream>
#include "../lib/DemodulateLibTypes.h" 
#include "../lib/DemodulateLibMath.h" 

int main(int argc, char * argv[])
{



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