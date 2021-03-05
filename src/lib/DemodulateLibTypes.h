#pragma once
#include <vector>

struct IQElement
{
	IQElement() {}
	IQElement(const float & i,const float & q):
		I(i),Q(q){}

	~IQElement(){}

	IQElement(const IQElement & e)
	{
		I = e.I;
		Q = e.Q;
	}

	IQElement & operator = (const IQElement & e)
	{
		if (this != &e)
		{
			I = e.I;
			Q = e.Q;
		}
		return *this;
	}

	IQElement GetConjugated() const
	{
		return IQElement(I, -Q);
	}

	IQElement & Conjugate()
	{
		Q = -Q;
		return *this;
	}

	float getPhase() const
	{
		return atan2f(Q, I);
	}

	float I;
	float Q;
};

typedef std::vector<IQElement> IQvec;
typedef std::vector <float> Flvec;