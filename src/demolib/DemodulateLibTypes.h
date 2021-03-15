#pragma once
#include <vector>
#include <cmath>
#include <fstream>

struct IQElement;


//Constants
constexpr float PI_f = 3.14159265358979323846f;

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

	float Magnitude() const
	{
		return sqrtf(I * I + Q * Q);
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


inline std::ostream & operator<<(std::ostream & s, const IQElement & e)
{
	s << e.Re << " " << e.Im << "\n";
	return s;
}

bool operator > (const IQElement & e1, const IQElement & e2)
{
	return e1.Magnitude() > e2.Magnitude();
}

typedef IQElement IQF;
