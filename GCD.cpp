#include <iostream>

using namespace std;

int gcd(int a, int b)
{
	int div = 0;
	if(a<0)
	{
		a *= -1;
	}
	if(b<0)
	{
		b *= -1;
	}
	if(!a)
	{
		return b;
	}
	else if(!b)
	{
		return a;
	}
	int max = a;
	if(a>b)
	{
		max = b;
	}
	for(int i = 1; i<=max; i++)
	{
		if(!(a%i) && !(b%i))
		{
			div = i;
		}
	}
	return div;
}

#ifndef MARMOSET_TESTING

int main()
{
	cout<<gcd(-6, -15)<<endl;
}

#endif