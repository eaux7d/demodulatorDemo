#pragma once
#include "DemodulateLibTypes.h"


//Core
void DemodulateAm(Flvec & output, const  IQvec & source);
void DemodulateFm(Flvec & output, const IQvec & source);
void ApplyFilter(IQvec & src,const float * filter, const int & size);

//HelpMath
IQElement RotateElement(const IQElement & a, const IQElement & b);


