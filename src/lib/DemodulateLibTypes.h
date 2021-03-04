#pragma once
#include <vector>

struct IQElement
{
	IQElement(float const & i, float const & q):
		I(i),Q(q){}

	~IQElement(){}

	IQElement(IQElement const & e)
	{
		I = e.I;
		Q = e.Q;
	}

	IQElement & operator = (IQElement const & e)
	{
		if (this != &e)
		{
			I = e.I;
			Q = e.Q;
		}
		return *this;
	}

	float I;
	float Q;
};

typedef std::vector<IQElement> IQvec;