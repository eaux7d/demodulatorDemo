#pragma once
#include <vector>
#include "demolib\DemodulateLibTypes.h"
#include "demolib\Tasks.hpp"

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

