#include <iostream>
#include <math.h>
#include "ClassyPoly.h"

using namespace std;

Polynomial Polynomial::dx() const
{
	return this->derivative();
}

float Polynomial::operator()(const float x) const
{
	return this->evaluate(x);
}

Polynomial Polynomial::operator+(const Polynomial& p) const
{
	return this->add(p);
}

Polynomial Polynomial::operator*(const Polynomial& p) const
{
	int new_degree = _degree + p._degree;
	
	float* y;
	y = new float[new_degree+1];
	if(_degree == 0)
	{
		for(int i = 0; i<=p._degree; i++)
		{
			y[i] = _coeff[0] * p._coeff[i];
		}
	}
	else if(p._degree == 0)
	{
		for(int i = 0; i<=_degree; i++)
		{
			y[i] = p._coeff[0] * _coeff[i];
		}
	}
	else
	{
		for(int k = 0; k<=new_degree; k++)
		{
			y[k] = 0;
		}
		for(int i = 0; i<=_degree; i++)
		{
			for(int j = 0; j<=p._degree; j++)
			{
				y[i+j] += _coeff[i] * p._coeff[j];
				if(y[i+j]<0.00001 && y[i+j]>-0.00001)
				{
					y[i+j] = 0;
				}
			}
		}
	}
	Polynomial p_new = Polynomial(new_degree, y);
	delete[] y;
	return p_new;
}

void Polynomial::operator=(const Polynomial& p)
{
	_degree = p._degree;
	delete[] _coeff;
	_coeff = new float[_degree+1];
	for(int i = 0; i<=_degree; i++)
	{
		_coeff[i] = p._coeff[i];
	}
}

bool Polynomial::operator==(const Polynomial& p) const
{
	int rc = 1;
	float del = 0;
	float rat = 0;
	if(_degree<0 || p._degree<0)
	{
		rc = 0;
	}
	else if(_degree != p._degree)
	{
		rc = 0;
	}
	else
	{
		for(int i = 0; i<=p._degree; i++)
		{
			del = _coeff[i] - p._coeff[i];
			if(_coeff[i]<0.00001 && p._coeff[i]<0.00001 && _coeff[i]>-0.00001 && p._coeff[i]>-0.00001)
			{
				rc = 1;
			}
			else if(del>0)
			{
				rat = del/_coeff[i];
				if(rat>0.00001)
				{
					rc = 0;
				}
			}
			else if(del<0)
			{
				rat = (-1*del)/p._coeff[i];
				if(rat>0.00001)
				{
					rc = 0;
				}
			}
		}
	}
	return rc;
}

Polynomial::Polynomial(const Polynomial& p)
{
	if(p._degree<0)
	{
		_degree = -1;
		_coeff = new float[1];
	}
	else
	{
		_degree = p._degree;
		_coeff = new float[p._degree+1];
		for(int i = 0; i<=p._degree; i++)
		{
			_coeff[i] = p._coeff[i];
		}
	}
}

Polynomial::Polynomial(const int degree, const float coeff[])
{
	if(degree<0)
	{
		_degree = -1;
		_coeff = new float[1];
	}
	else
	{
		_degree = degree;
		_coeff = new float[degree+1];
		for(int i = 0; i<=degree; i++)
		{
			_coeff[i] = coeff[i];
		}
	}
}

Polynomial::~Polynomial()
{
	delete[] _coeff;
}

float Polynomial::evaluate(const float x) const
{
	float result = 0.0;
	
	if(_degree<0)
	{
		return NAN;
	}
	else
	{
		for(int i = 0; i<=_degree; i++)
		{
			result = result*x + _coeff[i];
		}
		if(result<0.00001 && result>-0.00001)
		{
			result = 0.0;
		}
	}
	return result;
}

Polynomial Polynomial::add(const Polynomial& pIn) const
{
	int diff = 0;
	float* y;
	
	if(pIn._degree<0 || _degree<0)
	{
		y = new float[1];
		
		Polynomial p = Polynomial(-1, y);
		delete[] y;
		return p;
	}
	else if(_degree>pIn._degree)
	{
		y = new float[_degree+1];
		Polynomial p = Polynomial(_degree, y);
		
		diff = _degree - pIn._degree;
		for(int i = 0; i<diff; i++)
		{
			p._coeff[i] = _coeff[i];
		}
		
		for(int i = diff; i<=_degree; i++)
		{
			p._coeff[i] = _coeff[i] + pIn._coeff[i-diff];
		}
		delete[] y;
		return p;
	}
	else if(pIn._degree>_degree)
	{
		y = new float[pIn._degree+1];
		Polynomial p = Polynomial(pIn._degree, y);
		
		diff = pIn._degree - _degree;
		for(int i = 0; i<diff; i++)
		{
			p._coeff[i] = pIn._coeff[i];
		}
		
		for(int i = diff; i<=pIn._degree; i++)
		{
			p._coeff[i] = _coeff[i-diff] + pIn._coeff[i];
		}
		delete[] y;
		return p;
	}
	else if(_degree == pIn._degree)
	{
		y = new float[pIn._degree+1];
		Polynomial p = Polynomial(pIn._degree, y);
		
		for(int i = 0; i<=_degree; i++)
		{
			p._coeff[i] = _coeff[i] + pIn._coeff[i];
		}
		delete[] y;
		return p;
	}
	y = new float[_degree+1];
		
	Polynomial p = Polynomial(-1, y);
	delete[] y;
	return p;
}

Polynomial Polynomial::derivative() const
{
	if(_degree<0)
	{
		float* y;
		y = new float[1];
		Polynomial p = Polynomial(-1, y);
		delete[] y;
		return p;
	}
	int x;
	x = _degree-1;
	
	float* y;
	y = new float[_degree];
	
	Polynomial p = Polynomial(x, y);
	
	p._degree = _degree-1;
	for (int i = 0; i<_degree; i++)
	{
		p._coeff[i] = _coeff[i]*(_degree-i);
	}
	delete[] y;
	return p;
}

#ifndef MARMOSET_TESTING

int main()
{
	float coefficients1[] = {1, -2, 1};
	float coefficients2[] = {4, 2, 3};
	Polynomial P1(2, coefficients1);
	Polynomial P2(2, coefficients2);
	cout<<P1<<endl;
	cout<<P2<<endl;
	cout<<(P2.dx())<<endl;
}

#endif