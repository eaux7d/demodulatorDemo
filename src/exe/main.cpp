#include <fstream>
#include <iostream>

int main()
{
	std::fstream fin("E:/stc/1-AM/am.flt",std::fstream::binary|std::fstream::in);
	std::ofstream fout("E:/stc/1-AM/out.txt");

	if (!fin)
	{
		std::cerr << "Can't open!";
		return 1;
	}

	float r = 0.f, i = 0.f;

	while (!fin.eof())
	{
		fin.read((char *)&r, sizeof(float));
		fin.read((char *)&i, sizeof(float));

		fout << r << " " << i << "\n";
	}

	return 0;
}