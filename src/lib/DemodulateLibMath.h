#pragma once
#include "DemodulateLibTypes.h"


void demodulateAm(float * output, IQvec const & source);
void demodulateFm(float * output, IQvec const & source);