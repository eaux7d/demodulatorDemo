#pragma once
#include "DemodulateLibTypes.h"


//Core
void DemodulateAm(std::vector<float> & output,   std::vector<IQElement> & source);
void DemodulateFm(std::vector<float> & output,  std::vector<IQElement> & source);
void ApplyFilter(std::vector<IQElement> & src,const float * filter, const int & size);

//HelpMath
IQElement RotateElement(const IQElement & a, const IQElement & b);
