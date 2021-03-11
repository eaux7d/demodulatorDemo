#pragma once
#include "DemodulateLibTypes.h"

//Tasks
template <typename T>
void Diff(const std::vector<T> & src, std::vector<T> & out);

template <typename T>
void Rectpulse(const std::vector<T> & src, std::vector<T> & out, size_t n);

template <typename T>
int CountMoreThan(const std::vector<T> & src,const T & val);

void PhaseMod(const Ivec & src, IQvec & out, size_t M);

void FindLocalPeaks(const Flvec & src, STvec & idx_out, size_t win, float level);