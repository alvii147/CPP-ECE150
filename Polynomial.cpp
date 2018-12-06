#include <iostream>
#include <math.h>

using namespace std;

struct Polynomial
{
	int degree;
	float* coeff;
};

float evaluate(const Polynomial p, const float x)
{
	float result = 0.0;
	
	if(p.degree<0)
	{
		return NAN;
	}
	
	for(int i = 0; i<=p.degree; i++)
	{
		result = result*x + p.coeff[i];
	}
	
	return result;
}

Polynomial add(const Polynomial p1, const Polynomial p2)
{
	int diff = 0;
	Polynomial addition;
	if(p1.degree<0 || p2.degree<0)
	{
		addition.degree = -1;
		return addition;
	}
	
	if(p1.degree>p2.degree)
	{
		addition.degree = p1.degree;
		diff = p1.degree-p2.degree;
		addition.coeff = new float[p1.degree];
		for(int i = 0; i<=diff; i++)
		{
			addition.coeff[i] = p1.coeff[i];
			//cout<<"f "<<p1.coeff[i]<<endl;
		}
		int l = 0;
		for(int i = diff; i<=p1.degree; i++)
		{
			addition.coeff[i] = p1.coeff[i]+p2.coeff[l];
			l++;
		}
	}
	else if(p2.degree>p1.degree)
	{
		addition.degree = p2.degree;
		diff = p2.degree-p1.degree;
		addition.coeff = new float[p2.degree];
		for(int i = 0; i<=diff; i++)
		{
			addition.coeff[i] = p2.coeff[i];
			//cout<<"f "<<p1.coeff[i]<<endl;
		}
		int l = 0;
		for(int i = diff; i<=p2.degree; i++)
		{
			addition.coeff[i] = p1.coeff[l]+p2.coeff[i];
			l++;
		}
	}
	else
	{
		addition.degree = p1.degree;
		addition.coeff = new float[p1.degree];
		for(int i = 0; i<=p1.degree; i++)
		{
			addition.coeff[i] = p1.coeff[i] + p2.coeff[i];
		}
	}
	
	return addition;
}

Polynomial derivative(const Polynomial pIn)
{
	Polynomial der;
	
	if(pIn.degree == 0)
	{
		der.degree = 0;
		der.coeff = new float[1];
		der.coeff[0] = 0;
		return der;
	}
	
	
	der.degree = pIn.degree - 1;
	der.coeff = new float[pIn.degree - 1];
	
	if(pIn.degree == 0)
	{
		der.degree = 0;
		der.coeff[0] = 0;
		return der;
	}
	
	
	for(int k = 0; k<=der.degree; k++)
	{
		der.coeff[k] = pIn.coeff[k]*(der.degree-k+1);
	}
	
	return der;
}

int displayPolynomial(const Polynomial p) {
	if (p.degree < 0)
	{
		cerr<<"Parameter p is not a polynomial; p.degree = "<<p.degree<<endl;
		return -1;
	}
	cout<<"\"";
	for(int i = 0; i < p.degree; ++i)
	{
		if(p.coeff[i] == 1)
		{
			cout<<"x";
		}
		else
		{
			cout<<p.coeff[i]<<"x";
		}
		if ((p.degree - i) > 1)
		{
			cout<<"^"<<(p.degree - i);
		}
		cout <<"+";
	}
	cout<<p.coeff[p.degree]<<"\"";
	return 0;
}

#ifndef MARMOSET_TESTING

int main()
{
	float coeff[] = {1, 2, 3};   // x^2 + 2x + 3
	int degree = 2;
	Polynomial p0;
	Polynomial p1;
	Polynomial p2;
	
	p0.degree = 0;
	p0.coeff = coeff;
	p1.degree = 1;
	p1.coeff = coeff;
	p2.degree = 2;
	p2.coeff = coeff;
	
	cout << "When x = 2.2, ";
	displayPolynomial(p0);
	cout << " evalates to: " << evaluate(p0,2.2) << endl << endl;
	
	cout << "When x = 2.2, ";
	displayPolynomial(p1);
	cout << " evalates to: " << evaluate(p1,2.2) << endl << endl;
	
	cout << "When x = 2.2, ";
	displayPolynomial(p2);
	cout << " evalates to: " << evaluate(p2,2.2) << endl << endl;
	
	Polynomial p = add(p1,p2);
	cout << "p1 + p2 =  ";
	displayPolynomial(p);
	cout << endl;
	
	Polynomial pDer = derivative(p2);
	cout << "dp/dx =  ";
	displayPolynomial(pDer);
	cout << endl;
	
	return 0;
}

#endif