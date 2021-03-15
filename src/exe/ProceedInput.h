#pragma once
#include <vector>
#include "demolib\DemodulateLibTypes.h"

void ProceedIQInput(std::vector<IQElement> & input, std::fstream & fout, char mode);
void ProceedFlInput(const std::vector<float> & input, std::fstream & fout, char mode,float param);

template<typename T>
std::vector<T> InputFromFile(std::fstream & in)
{
	std::vector<T> vec;

	int size = 0;

	in.seekg(0, std::ifstream::end);
	size = in.tellg() / (sizeof(T));
	vec.resize(size);
	in.seekg(0, std::ifstream::beg);

	in.read((char *)&vec[0], sizeof(T) * size);

	return vec;
}