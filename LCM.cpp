#include <iostream>

using namespace std;

int lcm(int a, int b)
{
	if(a<0)
	{
		a *= -1;
	}
	if(b<0)
	{
		b *= -1;
	}
	if(!a && !b)
	{
		return 0;
	}
	if(!a)
	{
		return b;
	}
	if(!b)
	{
		return a;
	}
	int lowestCM = 0;
	int max = a*b;
	int i = 1;
	while(i<=max)
	{
		if(!(i%a) && !(i%b))
		{
			lowestCM = i;
			i = max+1;
		}
		i++;
	}
	return lowestCM;
}

#ifndef MARMOSET_TESTING

int main()
{
	cout<<lcm(-9, 12)<<endl;
}

#endif