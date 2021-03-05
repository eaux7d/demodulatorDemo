#pragma once
#include "DemodulateLibTypes.h"

//Core
void demodulateAm(Flvec & output,const IQvec & source);
void demodulateFm(Flvec & output,const IQvec & source);

//HelpMath
IQElement RotateElement(const IQElement & a, const IQElement & b);
