#pragma once
#include <vector>

struct IQElement;

//Constants
constexpr float PI = 3.14159265358979323846f;

typedef std::vector<IQElement> IQvec;
typedef std::vector <float> Flvec;
typedef std::vector<int> Ivec;
typedef std::vector<size_t> STvec;

struct IQElement
{
	IQElement() {}
	IQElement(const float & i,const float & q):
		I(i),Q(q){}

	~IQElement(){}

	IQElement(const IQElement & e):
		I(e.I),Q(e.Q){}

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

	IQElement operator+(const IQElement & e)
	{
		return IQElement(I + e.I, Q + e.Q);
	}

	IQElement operator*(const float & val)
	{
		return IQElement(I * val,Q * val);
	}

	IQElement & operator+=(const IQElement & e)
	{
		I += e.I;
		Q += e.Q;

		return *this;
	}

	union
	{
		struct { float I, Q; };
		struct { float Re, Im; };
	};

};
